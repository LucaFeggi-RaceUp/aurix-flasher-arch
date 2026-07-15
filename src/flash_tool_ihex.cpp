// MIT License

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdio>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include <iostream>
#include <inttypes.h> // PRIx64
#include "elf_parser.hpp"

#if linux

#include <sys/time.h>

#include <ctype.h>

#endif

#if defined(_WIN32)

#endif

#include "tas_client_rw.h"
#include "tas_utils.h"
#include "tas_device_family.h"


#define MCD_CORE_STATE_UNKNOWN  0x00000000
#define MCD_CORE_STATE_RUNNING  0x00000001
#define MCD_CORE_STATE_HALTED  0x00000002
#define MCD_CORE_STATE_DEBUG  0x00000003

void flasher_exit(int error);
/* this loads an hex file into the memory */
void load_file_hex (char *filename, int verbose);
/* this loads an elf file into the memory */
void load_file_elf (char *filename, int verbose, int check_hex);

/* this writes a part of memory[] to an intel hex file */
void
save_file (char *command);

/* this is used by load_file_hex to get each line of intex hex */
int
parse_hex_line (char *theline, int bytes[], unsigned int *addr, int *num, int *code);
int
parse_hex_line_addr (char *theline, int bytes[], unsigned int *addr, int *num, int *code);

/* this does the dirty work of writing an intel hex file */
/* caution, static buffering is used, so it is necessary */
/* to call it with end=1 when finsihed to flush the buffer */
/* and close the file */
/* actually the function is not used */
void
hexout (FILE *fhex, int byte, int memory_location, int end);

#define MEMTYPE_PFLASH 1
#define MEMTYPE_RAM 2
#define MEMTYPE_DFLASH 3
#define MEMTYPE_UCB 4

// TAS splits one large host transfer into 1 KiB PL0 transactions. The TC375
// target used here reports 24 PL0 transaction records, so keep each host
// transfer comfortably below that limit.
static const unsigned int TAS_SAFE_RW_CHUNK = 16 * 1024;

int
init_memory_buffers (int mode);
int
insert_memory_buffer (int i, unsigned int addr, unsigned int addr_mirror, unsigned int length, unsigned int page_size,
		char memtype, int blocks);
int set_memory_value (unsigned int addr, unsigned char value);
int get_memory_value (unsigned int addr, unsigned char* pvalue);
int
unset_memory_value (unsigned int addr);
unsigned char*
get_memory_buffer (unsigned int dst, unsigned int *paddr, unsigned int *plength);
int
analyze_memory_buffer (int list);

int do_status(CTasClientRw *client, int *status);
int do_write_mem(CTasClientRw *client, unsigned int addr, unsigned int data);
int do_read_mem(CTasClientRw *client, unsigned int addr, unsigned int *data);
int do_run(CTasClientRw *client);
int target_download_ram(CTasClientRw *client, char *pname);
int target_download_init(CTasClientRw *client);
int target_download_flash_double(CTasClientRw *client, char *pname_hex, char *pname_elf, int emul);
int target_perf_ram(CTasClientRw *client);
int device_tc2xx(void);
int device_tc3xx(void);
int device_tc4xx(void);
void print_sections(std::vector<elf_parser::section_t> &sections);
void print_segments(std::vector<elf_parser::segment_t> &segments);

int memory[65536]; /* the memory is global */
extern unsigned int chip_id;
extern int args_frequency;
extern int args_opt_flash;
extern int args_page_value;
extern int args_mem_list;
extern int args_map;
extern int args_ucb;
extern int args_erase;
extern int args_ver;
extern int args_log;
//if set DEBUG to 1 tons of additional log informations are generated
//#define DEBUG 0

#define debug_printf(args ...) if (args_log) printf(args)



/* this a memory element */
/* if you load a hex file, you will get a byte which has to be stored on address */
/* the address can be anything (please have here in mind that also the Intel Hex File can contain unvalid address */
/* if *data was set (the address is valid for this memory element), *status will get an update, so it is clear which cell is part of the Intel Hex or not */
/* later on the info in *status can be taken to do adjustements, e.g. page adapatations etc. */

typedef struct
{
	int was_used; //shows if the memory region was touched
	int valid; //the entry is valid
	unsigned int addr; //the primary address, uncached
	unsigned int addr_mirror; //the secondary address, cached
	unsigned int page_size; //has the memory page restriction, e.g. individual bytes can not be written
	int length; //length of the memory in bytes
	unsigned char *data; //the content
	char *status; //the status of the content
	char memtype;
	int specific;
	int blocks; //the memel can be divided in subblocks, minimum is 1, length divided by blocks should always be a log 2 value, e.g. 0x4000, 0x2000, ....
	int *blocks_used; //the memel can be divided in subblocks
	unsigned int base_pfi;
	unsigned int base_cpu;
} tmemel;
#define BYTE_SET_CONTENT 1
#define BYTE_SET_PAGE 2
#define BYTE_SET_EMPTY 0

/* support maximum 2048 memory entries */
#define MAX_memel 2048
tmemel memel[MAX_memel];

/* It says to target RUN */
/* The code will be started on the target, till it will be stopped via debug instruction */
int
do_run (CTasClientRw *client)
{
	int ret;
	ret = do_write_mem (client, 0xF881FD00, 0x4); //DBGSR HALT[1]=1, HALT[0]=0
	if (ret != 0)
	{
		printf ("Error: Run Client\n");
		exit (1);
	}
	return ret;
}

/*writes 32bits to address*/
int
do_write_mem (CTasClientRw *client, unsigned int addr, unsigned int data)
{
	int ret = client->write32 ((addr & 0xFFFFFFFE), data);
	if (ret != 0)
	{
		printf ("Error: WriteMemory Addr=%8.8x\n", addr);
		exit (1);
	}
	if (ret != 0)
		return -1;
	return 0;
}

/*reads 32bit from address */
int
do_read_mem (CTasClientRw *client, unsigned int addr, unsigned int *data)
{
	int ret = client->read32 ((addr & 0xFFFFFFFE), &data[0]);
	if (ret != 0)
	{
		printf ("Error: ReadMemory Addr=%8.8x\n", addr);
		exit (1);
	}

	if (ret != 0)
		return -1;
	return ret;
}

/*gives the status, running means the target executes still code, halted means that the target was stoppe by debug instruction or other event */
int
do_status (CTasClientRw *client, int *status)
{
	/*		MCD_CORE_STATE_UNKNOWN = 0x00000000,   < Target core state is unknown.
   MCD_CORE_STATE_RUNNING = 0x00000001, < Target core is running.
   MCD_CORE_STATE_HALTED = 0x00000002,  < Target core is halted.
   MCD_CORE_STATE_DEBUG = 0x00000003,   < Target core is in debug mode.
	 */
	unsigned int val;
	unsigned int pc;
	int ret;
	ret = do_read_mem (client, 0xF881FD00, &val); //read DBGSR
	val = val & 0x6;
	{
		if (val == 0x0)
		{
			*status = MCD_CORE_STATE_RUNNING;
		}
		if (val == 0x2)
		{
			*status = MCD_CORE_STATE_HALTED;
		}
	}
	//ret=do_read_mem(client,0xF881FE08,&pc); //read the Programmcounter
	//printf("do_status %d %x pc=%x\n",*status,val,pc);
	return -1;
}

/* writes a continues memory block to target */
/* the transfer is done in chunks small enough for the TAS PL0 transaction limit */
int
do_write_mem_blk (CTasClientRw *client, unsigned int addr, unsigned int len, unsigned char *pdata)
{
	unsigned int i;
	unsigned int addr_tr = addr;

	i = 0;
	while (len != 0)
	{
		if (len <= TAS_SAFE_RW_CHUNK)
		{
			tas_rw_trans_st trans =
			{ addr_tr, len, 0, 0, TAS_RW_TT_WR, &pdata[i] };
			tasutil_assert (client->execute_trans (&trans, 1));
			break;
		}
		else
		{
			//long
			tas_rw_trans_st trans =
			{ addr_tr, TAS_SAFE_RW_CHUNK, 0, 0, TAS_RW_TT_WR, &pdata[i] };
			tasutil_assert (client->execute_trans (&trans, 1));
			i += TAS_SAFE_RW_CHUNK;
			addr_tr += TAS_SAFE_RW_CHUNK;
			len -= TAS_SAFE_RW_CHUNK;
		}

	}
	return 0;
}

int
do_read_mem_blk (CTasClientRw *client, unsigned int addr, unsigned int len, unsigned char *pdata)
{
	unsigned int i;
	unsigned int addr_tr = addr;

	i = 0;
	while (len != 0)
	{
		if (len <= TAS_SAFE_RW_CHUNK)
		{
			tas_rw_trans_st trans =
			{ addr_tr, len, 0, 0, TAS_RW_TT_RD, &pdata[i] };
			tasutil_assert (client->execute_trans (&trans, 1));
			break;
		}
		else
		{
			//long
			tas_rw_trans_st trans =
			{ addr_tr, TAS_SAFE_RW_CHUNK, 0, 0, TAS_RW_TT_RD, &pdata[i] };
			tasutil_assert (client->execute_trans (&trans, 1));
			i += TAS_SAFE_RW_CHUNK;
			addr_tr += TAS_SAFE_RW_CHUNK;
			len -= TAS_SAFE_RW_CHUNK;
		}

	}
	return 0;
}

/* initialization of TAS and Target */
int
target_download_init (CTasClientRw *client)
{
	int ret = 0;
	ret = client->write32 (TAS_AM15_RW_ACC_HW_FREQUENCY, args_frequency, TAS_AM15); //set the frequency, default is 15.0MHZ
	//ret=client->write32(TAS_AM15_RW_ACC_HW_FREQUENCY,10000000,TAS_AM15); //set the frequency 10.0MHZ
	if (device_tc3xx())
	{
	ret = do_write_mem (client, 0xF881FD10, 0x2A); //SWEVT, if a debug insruction is executed, halt the device
	return (ret);
	}
	else if (device_tc4xx())
	{
	ret = do_write_mem (client, 0xF881FD10, 0x9); //SWEVT, if a debug insruction is executed, halt the device
	ret = do_write_mem (client, 0xF881FD14, 0x12); //SWEVT, if a debug insruction is executed, halt the device
	return (ret);
	}
	else
	{
    return (ret);
	}
}

/* Timing informations */
#if defined(_WIN32)
LONG delta_ms(SYSTEMTIME time_start,SYSTEMTIME time_end)
{
	LONG time_s;
	LONG time_e;
	time_s=time_start.wHour * 3600 * 1000 + time_start.wMinute *60 * 1000 + time_start.wSecond *1000 + time_start.wMilliseconds;
	time_e=time_end.wHour * 3600 * 1000 + time_end.wMinute *60 * 1000 + time_end.wSecond *1000 + time_end.wMilliseconds;
	return(time_e-time_s);
}
#endif

#if defined(linux)
uint64_t delta_ms(struct timeval time_start,struct timeval time_end)
{
	uint64_t time_s;
	uint64_t time_e;
	time_s=time_start.tv_sec * 1000000 + time_start.tv_usec;
	time_e=time_end.tv_sec * 1000000 + time_end.tv_usec;
	return((time_e-time_s)/1000);
}
#endif

void
print_time (void)
{
	if (args_log)
	{
#if defined(_WIN32)
		SYSTEMTIME time;
#endif

#if defined(linux)
		struct timeval time;
#endif

#if defined(_WIN32)
		GetSystemTime(&time);
		LONG time_s;
		time_s=time.wHour * 3600 * 1000 + time.wMinute *60 * 1000 + time.wSecond *1000 + time.wMilliseconds;
		debug_printf("Time=%ld ms ",time_s);
#endif

#if defined(linux)
		uint64_t time_s;
		gettimeofday(&time, NULL);
		time_s=time.tv_sec * 1000000 + time.tv_usec;
		debug_printf("Time=%ld ms",time_s);
#endif
	}
}

void
println_time (const char *info)
{
	if (args_log)
	{
#if defined(_WIN32)
		SYSTEMTIME time;
#endif

#if defined(linux)
		struct timeval time;
#endif

#if defined(_WIN32)
		GetSystemTime(&time);
		LONG time_s;
		time_s=time.wHour * 3600 * 1000 + time.wMinute *60 * 1000 + time.wSecond *1000 + time.wMilliseconds;
		debug_printf("-->Time=%ld ms  (%s)\n",time_s,info);
#endif

#if defined(linux)
		uint64_t time_s;
		gettimeofday(&time, NULL);
		time_s=time.tv_sec * 1000000 + time.tv_usec;
		debug_printf("-->Time=%ld ms   (%s)\n",time_s,info);
#endif
	}
}

int
target_pf_erase_sectors (CTasClientRw *client, unsigned int addr, int sector_cnt)
{
	int ret = 0;
	int i;
	unsigned int params[8];
	int sect_status;
	unsigned int value;
	int status;
	int timeout;
	if (args_erase==2) return 0; // do not erase
	println_time ("target_pf_erase_sectors Begin");
	//set PC to 0x70000000
	ret = do_write_mem (client, 0xF881FE08, 0x70000000); //PC
	ret = do_write_mem (client, 0xF881FF90, 0x70008000); //A4
	{
		status = -1;
		ret = do_status (client, &status);
	}
	params[0] = 0xA0000000;
	params[2] = addr; //the address of the memory to be erased
	params[3] = sector_cnt; //is 16k * 32 at maximum allowed to be erased as bundle is 32, should not cross the phyiscal boundary 512k
	params[4] = 0x2;
	ret = do_write_mem_blk (client, 0x70008000, 32, (unsigned char*) &params[0]);
	ret = do_run (client);
	timeout = 0;
	debug_printf("Erase Sector start @addr=%8.8x sectors=%d \n", params[2], params[3]);
	{
		status = -1;
		while (1 == 1)
		{
			ret = do_status (client, &status);
			//debug_printf("Erase Status %d \n", status);
			if (status != MCD_CORE_STATE_RUNNING)
			{
				ret = do_status (client, &status);
				ret = do_read_mem (client, 0x70008010, &value);
				if (value != 0)
				{
					printf ("Error: Target Erase Sector Timeout Sector Addr=%8.8x Sector_Cnt=%d\n", addr, sector_cnt);
					exit (1);
				}
				debug_printf("StatusExit Erase Status=%d Value=%8.8x timeout=%d\n", status, value, timeout);
				break;
			}
			if (timeout > 10000)
			{
				printf ("Error: Host Erase Sector Timeout Sector Addr=%8.8x Sector_Cnt=%d\n", addr, sector_cnt);
				exit (1);
			}
			timeout += 1;
		}
	}
	println_time ("target_pf_erase_sectors End");
	return 0;
}

/* downloads a file to target incl. flashing*/
/* pname is file name */
/* emul has to be set to zero */
int
target_verify_flash (CTasClientRw *client, int *blocks_delta)
{
	int ret = 0;
#if 1
	int i;
	unsigned int len;
	unsigned int addr;
	unsigned int begin_addr;
	unsigned char *pdata;
	unsigned int mem_buf[0x8000]; //128k
	unsigned int mem_el;
	unsigned int checksum;
	unsigned int target_addr;
	unsigned int target_param_addr;
	unsigned int value;
	unsigned int block_len;
	int status;
	int timeout;
	unsigned int params[8];
	*blocks_delta=0;

#if defined(_WIN32)
	SYSTEMTIME time_end;
	SYSTEMTIME time_start;
	LONG time_delta_ms;
#endif

#if defined(linux)
	struct timeval time_end;
	struct timeval time_start;
	uint64_t  time_delta_ms;
#endif

	ret = 0;
#if defined(_WIN32)
	GetSystemTime(&time_start);
#endif

#if defined(linux)
	gettimeofday(&time_start, NULL);
#endif
	target_addr = 0x70008000;
	target_param_addr = 0x70006000;
	debug_printf("Verify Content\n");
	memset (&mem_buf[0], 0, 65536);
	mem_el = 0;
	for (i = 0; i < MAX_memel; i += 1)
	{
		if ((mem_el * 4) > (sizeof(mem_buf) - 0x100))
			break;
		if ((memel[i].valid == 1) && (memel[i].was_used == 1) &&
				((memel[i].memtype == MEMTYPE_PFLASH) || (memel[i].memtype == MEMTYPE_DFLASH) || ((memel[i].memtype == MEMTYPE_UCB) && args_ucb)))
		{
			debug_printf("memel %d %x %x \n", i, memel[i].addr, memel[i].length);
			begin_addr = memel[i].addr; //the start address of the memory
			while (begin_addr < (memel[i].addr + memel[i].length))
			{
				//	  if (begin_addr < (memel[i].addr + memel[i].length))
				{
					pdata = get_memory_buffer (begin_addr, &addr, &len); /*provides a continues range of data which have to be written.*/
					if (pdata != NULL)
					{
						print_time ();
						debug_printf("Checksum %d Addr_Base=%8.8X Begin_addr=%8.8x Addr=%8.8X length=%8.8X\n", i,
								memel[i].addr, begin_addr, addr, len);
						block_len=memel[i].length/memel[i].blocks;
						if (len > block_len)
							len = block_len;
						if (((addr & (block_len-1)) + len) > block_len)
							len = (addr & ~(block_len-1)) + block_len - addr;
						//calculate the checksum
						checksum = 0;
						unsigned int *pdata32;
						pdata32 = (unsigned int*) &pdata[0];
						unsigned int mem_start=*pdata32;
						for (int ii = 0; ii < len; ii += 4)
						{
							checksum += *pdata32;
							pdata32++;
						}
						print_time ();
						debug_printf("Checksum %d Addr_Base=%8.8X Addr=%8.8X length=%8.8X checksum=%8.8x\n", i,
								memel[i].addr, addr, len, checksum);
						mem_buf[mem_el] = addr;
						mem_buf[mem_el + 1] = len;
						mem_buf[mem_el + 2] = checksum;
						mem_buf[mem_el + 3] = 0;
						mem_buf[mem_el + 4] = memel[i].base_pfi;
						mem_buf[mem_el + 5] = memel[i].base_cpu;
						mem_buf[mem_el + 6] = mem_start;
						mem_buf[mem_el + 7] = 0;
						mem_el += 8;
						begin_addr = addr + len; //addr+len was the given range to be programmed, next time use begin_addr to ask for a next valid block via get_memory_buffer
						//		  ret = do_write_mem_blk(client, target_addr0, len, &pdata0[0]);
						//		  print_time();debug_printf("BufferTransfer0 Buffer Done\n");
						//		  params[0] = 0xA0000000;
						//		  params[2] = addr;
						//		  params[3] = len;
						//		  params[4] = 0x1;
						//		  params[5] = target_addr0;
						//		  ret = do_write_mem_blk(client, target_param_addr0, 32, (unsigned char *)&params[0]);
						//		  print_time();debug_printf("BufferTransfer0 Command Done\n");
						//		  target_status0 = 1;
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	mem_buf[mem_el] = 0xFFFFFFFF;
	mem_buf[mem_el + 1] = 0xFFFFFFFF;
	mem_el += 2;
	debug_printf("Verify Memel=%d \n ", mem_el);
	ret = do_write_mem_blk (client, target_addr, mem_el * 4, (unsigned char*) &mem_buf[0]);
	params[0] = 0xA0000000;
	params[2] = 0;
	params[3] = 0;
	params[4] = 4;
	params[5] = target_addr;
	ret = do_write_mem_blk (client, target_param_addr, 32, (unsigned char*) &params[0]);
	ret = do_write_mem (client, 0xF881FE08, 0x70000000); //PC
	ret = do_write_mem (client, 0xF881FF90, target_param_addr); //A4
	ret = do_run (client);

	timeout = 0;
	debug_printf("Verify\n");
	{
		status = -1;
		while (1 == 1)
		{
			ret = do_status (client, &status);
			if (status != MCD_CORE_STATE_RUNNING)
			{
				ret = do_status (client, &status);
				ret = do_read_mem (client, target_param_addr + 0x10, &value);
				if (value != 0)
				{
					printf ("Error: Verify %d\n", value);
					ret = do_read_mem_blk (client, target_addr, mem_el * 4, (unsigned char*) &mem_buf[0]);
					printf ("Error: Read %d\n", ret);
					for (int ii = 0; ii < mem_el; ii += 8)
					{
						if (mem_buf[ii] == 0xFFFFFFFF)
							break;
						debug_printf("%d %8.8x %8.8x", ii, mem_buf[ii], mem_buf[ii + 1]);
						debug_printf(" %8.8x %8.8x", mem_buf[ii + 2], mem_buf[ii + 3]);
						debug_printf(" %8.8x %8.8x", mem_buf[ii + 4], mem_buf[ii + 5]);
						debug_printf(" %8.8x %8.8x\n", mem_buf[ii + 6], mem_buf[ii + 7]);
					}
					exit (1);
				}
				debug_printf("StatusExit Verify Status=%d Value=%8.8x timeout=%d\n", status, value, timeout);
				break;
			}
			if (timeout > 10000)
			{
				printf ("Error: Verify Timeout=%d \n", timeout);
				for (int ii = 0; ii < mem_el; ii += 8)
				{
					if (mem_buf[ii] == 0xFFFFFFFF)
						break;
					debug_printf("%d %8.8x %8.8x", ii, mem_buf[ii], mem_buf[ii + 1]);
					debug_printf(" %8.8x %8.8x", mem_buf[ii + 2], mem_buf[ii + 3]);
					debug_printf(" %8.8x %8.8x", mem_buf[ii + 4], mem_buf[ii + 5]);
					debug_printf(" %8.8x %8.8x\n", mem_buf[ii + 6], mem_buf[ii + 7]);
				}
				exit (1);
			}
			timeout += 1;
		}
	}
	println_time ("Verify End");

	ret = do_read_mem_blk (client, target_addr, mem_el * 4, (unsigned char*) &mem_buf[0]);
	if (ret != 0)
	{
		printf ("Error: Verify Read \n");
		exit (1);
	}
	//we can now remove the itmes which are already part of the flash
	for (int ii = 0; ii < mem_el; ii += 8)
	{
		if (mem_buf[ii] == 0xFFFFFFFF)
			break;
		//precondition is
		//mem_buf[i+3] must be 0xAAAAAAAA if checksum was ok, if checksum wrong 0xEEEEEEEE;
		if ((mem_buf[ii + 3] != 0xAAAAAAAA) && (mem_buf[ii + 3] != 0xEEEEEEEE))
		{
			printf ("Error: Checksum from Target \n");
			printf ("%d %8.8x %8.8x", ii, mem_buf[ii], mem_buf[ii + 1]);
			printf (" %8.8x %8.8x", mem_buf[ii + 2], mem_buf[ii + 3]);
			printf (" %8.8x %8.8x", mem_buf[ii + 4], mem_buf[ii + 5]);
			printf (" %8.8x %8.8x\n", mem_buf[ii + 6], mem_buf[ii + 7]);
			exit (1);
		}
		if ((mem_buf[ii + 3] == 0xAAAAAAAA))
		{
			//do the correction
			debug_printf("Checksum pass remove the content \n");
			debug_printf("%d %8.8x %8.8x", ii, mem_buf[ii], mem_buf[ii + 1]);
			debug_printf(" %8.8x %8.8x", mem_buf[ii + 2], mem_buf[ii + 3]);
			debug_printf(" %8.8x %8.8x", mem_buf[ii + 4], mem_buf[ii + 5]);
			debug_printf(" %8.8x %8.8x\n", mem_buf[ii + 6], mem_buf[ii + 7]);
			for (unsigned int jj = mem_buf[ii]; jj < (mem_buf[ii] + mem_buf[ii + 1]); jj += 1)
			{
				unset_memory_value (jj);
			}
		}
		else
		{
			*blocks_delta+=1;
			debug_printf("Checksum no pass remove the content \n");
			debug_printf("%d %8.8x %8.8x", ii, mem_buf[ii], mem_buf[ii + 1]);
			debug_printf(" %8.8x %8.8x", mem_buf[ii + 2], mem_buf[ii + 3]);
			debug_printf(" %8.8x %8.8x", mem_buf[ii + 4], mem_buf[ii + 5]);
			debug_printf(" %8.8x %8.8x\n", mem_buf[ii + 6], mem_buf[ii + 7]);
		}
	}
	if (args_mem_list!=0)
	{
		printf("\nMemories changed after verify with Target\n");
	}
	analyze_memory_buffer (args_mem_list);
	if (args_mem_list!=0)
	{
		printf("\n");
	}

#if defined(_WIN32)
	GetSystemTime(&time_end);
#endif

#if defined(linux)
	gettimeofday(&time_end, NULL);
#endif
	debug_printf("Time to Verify in ms (Milliseconds) %ld \n", delta_ms (time_start, time_end));
#endif
	return (ret);
}

/* downloads a file to target incl. flashing*/
/* pname is file name */
/* emul has to be set to zero */
int
target_download_flash_double (CTasClientRw *client, char *pname_hex, char *pname_elf, int emul)
{
	int ret = 0;
#if 1
	int i;
	unsigned int len;
	unsigned int addr;
	unsigned char *pdata0;
	unsigned char *pdata1;
	unsigned int begin_addr;
	unsigned int target_addr0;
	unsigned int target_param_addr0;
	unsigned int target_status0;
	unsigned int target_addr1;
	unsigned int target_param_addr1;
	unsigned int target_status1;
	unsigned int params[8];
	int timeout0 = 0;
	int timeout1 = 0;
	int addr_cont;
	int sect_cont;
	int status;
	int sect_status;
	unsigned int value;
#if defined(_WIN32)
	SYSTEMTIME time_end;
	SYSTEMTIME time_start;
	LONG time_delta_ms;
#endif

#if defined(linux)
	struct timeval time_end;
	struct timeval time_start;
	uint64_t  time_delta_ms;
#endif

	ret = 0;
#if defined(_WIN32)
	GetSystemTime(&time_start);
#endif

#if defined(linux)
	gettimeofday(&time_start, NULL);
#endif
	println_time ("init_memory_buffers Begin");
	init_memory_buffers (1);  //initialize the memory buffers*/
	println_time ("init_memory_buffers End");
	println_time ("load_file Begin");
	if (pname_hex!=NULL) load_file_hex (pname_hex, 0); //loads the intel hex file to be flashed
	if (pname_elf!=NULL) load_file_elf (pname_elf, 0,(pname_hex!=NULL) && (pname_elf!=NULL)); //loads the elf file to be flashed
	println_time ("load_file End");
	debug_printf("Load FilE Done! \n");
	debug_printf("Time to Load in ms (Milliseconds) %ld \n", delta_ms (time_start, time_end));
	println_time ("analyze_memory_buffer Begin");
	analyze_memory_buffer (args_mem_list); //analyzes the loaded content and does corrections, e.g. pages,mirroring...
	println_time ("analyze_memory_buffer End");
#if defined(_WIN32)
	GetSystemTime(&time_end);
#endif
#if defined(linux)
	gettimeofday(&time_end, NULL);
#endif

	if (args_opt_flash == 1)
	{
		int block_delta=0;
		target_verify_flash (client,&block_delta);
	}
#if defined(_WIN32)
	GetSystemTime(&time_start);
#endif

#if defined(linux)
	gettimeofday(&time_start, NULL);
#endif

	// check the sectors to be erased
	if (emul == 1)
	{
		for (i = 0; i < MAX_memel; i += 1)
		{
			if ((memel[i].valid == 1) && (memel[i].was_used == 1))
			{
				//printf("Emul Erase Sector Used=%d Addr=%8.8X Addr_mirror=%8.8X length=%8.8X\n", i, memel[i].addr, memel[i].addr_mirror, memel[i].length);
			}
		}
	}

	if (args_erase==2) //erase all
	{
		i = 0;
			while (i < MAX_memel)
			{
				//we execute erase only on memories which where used, meaning the Intel Hex File contained data belonging to the memory region
				if ((memel[i].valid == 1) && (memel[i].memtype == MEMTYPE_PFLASH))
				{
					for (int jj = 0; jj < memel[i].blocks; jj += 1)
					{
						addr = memel[i].addr;
						target_pf_erase_sectors (client, addr, memel[i].blocks);
					}
				}
				i += 1;
			}
	}
	//sequential sectors can be erased, not crossing the physical boundaries
	else
	{
	i = 0;
	while (i < MAX_memel)
	{
		//we execute erase only on memories which where used, meaning the Intel Hex File contained data belonging to the memory region
		if ((memel[i].valid == 1) && (memel[i].was_used == 1) && (memel[i].memtype == MEMTYPE_PFLASH))
		{
			addr_cont = 0;
			sect_cont = 0;
			sect_status = 0;
			for (int jj = 0; jj < memel[i].blocks; jj += 1)
			{
				addr = memel[i].addr + jj * memel[i].length/memel[i].blocks;
				if (memel[i].blocks_used[jj] != 0)
				{
					if (sect_status == 1)
					{
						sect_status = 1;
						sect_cont += 1;
					}
					else
					{
						sect_status = 1;
						addr_cont = addr;
						sect_cont = 1;
					}
				}
				else
				{
					if (sect_status == 0)
					{
						sect_status = 0;
						addr_cont = 0;
						sect_cont = 0;
						sect_status = 0;
					}
					else
					{
						target_pf_erase_sectors (client, addr_cont, sect_cont);
						debug_printf("Erase PF Sector 1 start %8.8x sectors=%d \n", addr_cont, sect_cont);
						sect_status = 0;
						addr_cont = 0;
						sect_cont = 0;
						sect_status = 0;
					}
				}
				if (jj == (memel[i].blocks-1))
				{
					if (sect_status == 1)
					{
						target_pf_erase_sectors (client, addr_cont, sect_cont);
						debug_printf("Erase PF Sector 2 start %8.8x sectors=%d \n", addr_cont, sect_cont);
					}
				}
			}
		}
		i += 1;
	}
	}
	#if defined(_WIN32)
	GetSystemTime(&time_end);
#endif

#if defined(linux)
	gettimeofday(&time_end, NULL);
#endif
	debug_printf("Erase Done! \n");
	debug_printf("Time to Erase in ms (Milliseconds) %ld \n", delta_ms (time_start, time_end));
	printf ("::Erasing Flash memory .......... (Pass)\n");
#if defined(_WIN32)
	GetSystemTime(&time_start);
#endif
#if defined(linux)
	gettimeofday(&time_start, NULL);
#endif

	printf ("::Programming Flash memory .");
	if (emul == 0)
	{
		target_addr0 = 0x70008000;
		target_param_addr0 = 0x70006000;
		target_addr1 = 0x70010000;
		target_param_addr1 = 0x70006100;
		for (i = 0; i < MAX_memel; i += 1)
		{
			if ((memel[i].valid == 1) && (memel[i].was_used == 1) && (memel[i].memtype == MEMTYPE_PFLASH))
			{
				printf (".");
				fflush (stdout);
				debug_printf("memel %d %x %x \n", i, memel[i].addr, memel[i].length);
				begin_addr = memel[i].addr; //the start address of the memory
				target_status0 = 0;
				target_status1 = 0;
				while (1 == 1)
				{
					print_time ();
					debug_printf("Target0=%d Target1=%d\n", target_status0, target_status1);
					if (target_status0 == 0)
					{
						if (target_status1 == 1)
						{
							//set PC to 0x70000000
							print_time ();
							debug_printf("Start Program1\n");
							ret = do_write_mem (client, 0xF881FE08, 0x70000000); //PC
							ret = do_write_mem (client, 0xF881FF90, target_param_addr1); //A4
							ret = do_run (client);
							timeout1 = 0;
							target_status1 = 2;
						}
						if (begin_addr < (memel[i].addr + memel[i].length))
						{
							pdata0 = get_memory_buffer (begin_addr, &addr, &len); /*provides a continues range of data which have to be written.*/
							if (pdata0 != NULL)
							{
								if (len > 0x8000)
									len = 0x8000;
								begin_addr = addr + len; //addr+len was the given range to be programmed, next time use begin_addr to ask for a next valid block via get_memory_buffer
								print_time ();
								debug_printf(
										"BufferTransfer0 Flash Used=%d Addr_Base=%8.8X Addr=%8.8X targaddr=%8.8X length=%8.8X\n",
										i, memel[i].addr, addr, target_addr0, len);
								ret = do_write_mem_blk (client, target_addr0, len, &pdata0[0]);
								print_time ();
								debug_printf("BufferTransfer0 Buffer Done\n");
								params[0] = 0xA0000000;
								params[2] = addr;
								params[3] = len;
								params[4] = 0x1;
								params[5] = target_addr0;
								ret = do_write_mem_blk (client, target_param_addr0, 32, (unsigned char*) &params[0]);
								print_time ();
								debug_printf("BufferTransfer0 Command Done\n");
								target_status0 = 1;
							}
							else
							{
								target_status0 = 4;
							}
						}
						else
						{
							target_status0 = 4;
						}
					}
					if (target_status1 == 0)
					{
						if (target_status0 == 1)
						{
							//set PC to 0x70000000
							print_time ();
							debug_printf("Start Program0\n");
							ret = do_write_mem (client, 0xF881FE08, 0x70000000); //PC
							ret = do_write_mem (client, 0xF881FF90, target_param_addr0); //A4
							ret = do_run (client);
							timeout0 = 0;
							target_status0 = 2;
						}
						if (begin_addr < (memel[i].addr + memel[i].length))
						{
							pdata1 = get_memory_buffer (begin_addr, &addr, &len);
							if (pdata1 != NULL)
							{
								if (len > 0x8000)
									len = 0x8000;
								begin_addr = addr + len;
								print_time ();
								debug_printf(
										"BufferTransfer1 Flash Used=%d Addr_Base=%8.8X Addr=%8.8X targaddr=%8.8X length=%8.8X\n",
										i, memel[i].addr, addr, target_addr1, len);
								ret = do_write_mem_blk (client, target_addr1, len, &pdata1[0]);
								print_time ();
								debug_printf("BufferTransfer1 Buffer Done\n");
								params[0] = 0xA0000000;
								params[2] = addr;
								params[3] = len;
								params[4] = 0x1;
								params[5] = target_addr1;
								ret = do_write_mem_blk (client, target_param_addr1, 32, (unsigned char*) &params[0]);
								print_time ();
								debug_printf("BufferTransfer1 Command Done\n");
								target_status1 = 1;
							}
							else
							{
								target_status1 = 4;
							}
						}
						else
						{
							target_status1 = 4;
						}

					}
					status = -1;
					while (1 == 1)
					{
						ret = do_status (client, &status);
						println_time ("Waiting");
						timeout0 += 1;
						timeout1 += 1;
						if (timeout0 > 10000)
						{
							printf ("Error: Host Program Timeout Addr=%8.8x Len=%4.4x\n", addr, len);
							exit (1);
						}
						if (timeout0 > 10000)
						{
							printf ("Error: Host Program Timeout Addr=%8.8x Len=%4.4x\n", addr, len);
							exit (1);
						}
						if (status != MCD_CORE_STATE_RUNNING)
						{
							//read status
							if (target_status0 == 2)
							{
								ret = do_read_mem (client, target_param_addr0 + 0x10, &value);
								if (value != 0)
								{
									printf ("Error: Host Program Timeout Addr=%8.8x Len=%4.4x\n", addr, len);
									exit (1);
								}
								target_status0 = 0;
								print_time ();
								debug_printf("StatusExit Program0 Target0 Status=%d Value=%8.8x timeout=%d\n", status,
										value, timeout0);
							}
							if (target_status1 == 2)
							{
								ret = do_read_mem (client, target_param_addr1 + 0x10, &value);
								if (value != 0)
								{
									printf ("Error: Host Program Timeout Addr=%8.8x Len=%4.4x\n", addr, len);
									exit (1);
								}
								target_status1 = 0;
								print_time ();
								debug_printf("StatusExit Program1 Target1 Status=%d Value=%8.8x timeout=%d\n", status,
										value, timeout1);
							}
							break;
						}
					}
					//end of memory element reached
					if ((target_status0 == 4) && (target_status1 == 4))
					{
						break;
					}
				}
			}
		}
	}
#if defined(_WIN32)
	GetSystemTime(&time_end);
#endif

#if defined(linux)
	gettimeofday(&time_end, NULL);
#endif
	printf (". (Pass)\n");
	fflush (stdout);
	//doing now the erase/programing of UCBS, please be carefull here, you can brick the device
	if (args_ucb==1)
	{
		printf ("::Programming+Erasing UCB memory .");
		i = 0;
		while (i < MAX_memel)
		{
			//we execute erase only on memories which where used, meaning the Intel Hex File contained data belonging to the memory region
			if ((memel[i].valid == 1) && (memel[i].was_used == 1) && (memel[i].memtype == MEMTYPE_UCB))
			{
				for (int jj=0; jj<memel[i].blocks; jj+=1)
				{
					if ((memel[i].blocks_used[jj]!=0))
					{
						int block_len=memel[i].length/memel[i].blocks;
						debug_printf("Update UCB addr=%8.8x length=%4.4x\n",memel[i].addr+jj*block_len,block_len);
						ret = do_write_mem (client, 0xF881FE08, 0x70000000); //PC
						ret = do_write_mem (client, 0xF881FF90, 0x70006000); //A4
						{
							status = -1;
							ret = do_status (client, &status);
						}
						params[0] = 0xA0000000;
						params[2] = memel[i].addr+jj*block_len; //the address of the UCB memory to be erased
						params[4] = 0x3; //UCB Erase and copy
						params[5] = 0x70008000;
						ret = do_write_mem_blk (client, 0x70006000, 32, (unsigned char*) &params[0]); //the parameters
						ret = do_write_mem_blk (client, 0x70008000, block_len, (unsigned char*) &memel[i].data[jj*block_len]); //the data
						ret = do_run (client);
						int timeout;
						timeout = 0;
						debug_printf("Erase+Program UCB start @addr=%8.8x ucb_nr=%d \n", params[2], jj);
						status = -1;
						while (1 == 1)
						{
							ret = do_status (client, &status);
							//debug_printf("Erase Status %d \n", status);
							if (status != MCD_CORE_STATE_RUNNING)
							{
								ret = do_status (client, &status);
								ret = do_read_mem (client, 0x70006010, &value);
								if (value != 0)
								{
									printf("Error Erase+Program UCB start @addr=%8.8x ucb_nr=%d \n", params[2], jj);
									exit (1);
								}

								debug_printf("StatusExit Erase+Program UCB Status=%d Value=%8.8x timeout=%d\n", status, value, timeout);
								break;
							}
							if (timeout > 10000)
							{
								printf ("Error: Erase+Program UCB Timeout Sector Addr=%8.8x ucb_nr=%d\n", memel[i].addr+jj*block_len, jj);
								exit (1);
							}
							timeout += 1;
						}
					}
				}
			}
			i+=1;
		}

		printf (". (Pass)\n");
		fflush (stdout);
	}
	debug_printf("Time to Program in ms (Milliseconds) %ld \n", delta_ms (time_start, time_end));

	if (args_ver == 1)
	{
		int block_delta=0;
		printf ("::Verifying Flash memory ..");
		target_verify_flash (client,&block_delta);
		printf ("(Pass)\n");
		printf ("::Flash memory matches expected value ..");
		if (block_delta==0)
		{
			printf ("(Pass)\n");
		}
		else
		{
			printf ("(Fail)\n");
		}
	}
#endif
	return (ret);
}

/* a routing to measure the upload performance to the target */
int
target_perf_ram (CTasClientRw *client)
{
	unsigned char buf[0x10000];
	int ret = 0;
#if defined(_WIN32)
	SYSTEMTIME time_end;
	SYSTEMTIME time_start;
	LONG time_delta_ms;
#endif

#if defined(linux)
	struct timeval time_end;
	struct timeval time_start;
	uint64_t  time_delta_ms;
#endif

#if defined(_WIN32)
	GetSystemTime(&time_start);
#endif
#if defined(linux)
	gettimeofday(&time_start, NULL);
#endif
	unsigned int len = 0x8000;
	int loops = 10;
	for (int i = 0; i < loops; i += 1)
	{
		ret = do_write_mem_blk (client, 0x70000000, len, &buf[0]);
	}
#if defined(_WIN32)
	GetSystemTime(&time_end);
#endif

#if defined(linux)
	gettimeofday(&time_end, NULL);
#endif
	printf ("Time to Transfer in ms (Milliseconds) %ld \n", delta_ms (time_start, time_end));
	printf ("Transfer of %d bytes  Speed %f byte/sec \n", loops * len,
			((float) (loops * len)) / ((float) delta_ms (time_start, time_end) * 0.001f));
	return ret;
}

/* download the target routine to ram */
/* it is fixed by address 0x70000000 adn downloaded as one block */
int
target_download_ram (CTasClientRw *client, char *pname)
{
	int ret = 0;
	int status;
	init_memory_buffers (0);
	load_file_hex (pname, 1);
	analyze_memory_buffer (0);
	{
		unsigned int len;
		unsigned int addr;
		unsigned char *pdata;
		unsigned int i;
		pdata = get_memory_buffer (0x70000000, &addr, &len);
		debug_printf("Write Memory addr=%8.8X length=%8.8X \n", addr, len);
		ret = do_write_mem_blk (client, addr, len, &pdata[0]);
	}

	status = -1;
	ret = do_status (client, &status);
	debug_printf("Status CPU0 %d \n", status);
	//set PC to 0x70000000
	ret = do_write_mem (client, 0xF881FE08, 0x70000000);
	status = -1;
	ret = do_status (client, &status);
	debug_printf("Status CPU0 %d \n", status);
	return (ret);
}

/* provide of out the memories a valid block to be written, it starts to search with dst and delivers back paddr and plength, as continues block. */
/* if page is set, page gaps are overjumped */
unsigned char*
get_memory_buffer (unsigned int dst, unsigned int *paddr, unsigned int *plength)
{
	unsigned char *pret;
	int i, j;
	int banalyzed;
	int offs_0, offs_1;
	pret = NULL;
	//we have an address and want to set the value
	for (i = 0; i < MAX_memel; i += 1)
	{
		if ((dst >= memel[i].addr) && (dst < (memel[i].addr + memel[i].length - 1)) && (memel[i].valid == 1)
				&& (memel[i].was_used == 1))
		{
			j = dst - memel[i].addr;
			offs_0 = -1;
			offs_1 = -1;
			banalyzed = 0;
			while (banalyzed == 0)
			{
				if ((memel[i].status[j] != BYTE_SET_EMPTY) && (offs_0 == -1))
					offs_0 = j;
				if ((memel[i].status[j + memel[i].page_size] == BYTE_SET_EMPTY) && (offs_0 != -1) && (offs_1 == -1))
					offs_1 = j + memel[i].page_size - 1;
				if ((offs_0 != -1) && (offs_1 != -1))
				{
					banalyzed = 1;
				}
				j += memel[i].page_size;
				if (j >= (memel[i].length - memel[i].page_size))
				{
					if (offs_0 != -1)
					{
						offs_1 = memel[i].length - 1;
					}
					banalyzed = 1;
				}
			}

			if ((offs_0 == -1) || (offs_1 == -1))
				return (NULL);

			*paddr = offs_0 + memel[i].addr;
			*plength = offs_1 - offs_0 + 1;
			pret = &memel[i].data[offs_0];
			return (pret);
		}
	}
	return (pret);

}


int get_memory_cks (void)
{
	int ret;
	int i, j, valid_addr;
	unsigned int rel_addr;
	int cks=0;
	ret = -1;
		//we have an address and want to set the value
		for (i = 0; i < MAX_memel; i += 1)
		{
			for (int jj=0; jj<memel[i].length; jj+=1)
			{
				if (memel[i].valid == 1) cks+=memel[i].data[jj];
			}
		}
	return (cks);
}


/* set the value in the memory, call from ihex import*/
/* BYTE_SET_EMPTY, byte is not set */
/* BYTE_SET_CONTENT, byte was directly set */
/* BYTE_SET_PAGE, a byte was set via BYTE_SET_CONTENT, bytes in the page are not set, but will be written. */
int get_memory_value (unsigned int addr, unsigned char* pvalue)
{
	int ret;
	int i, j, valid_addr;
	unsigned int rel_addr;
	static int i_cache = -1;

	ret = -1;
	if (i_cache != -1)
	{
		i = i_cache;
		valid_addr = -1;
		if ((addr >= memel[i].addr) && (addr < (memel[i].addr + memel[i].length)) && (memel[i].valid == 1))
		{
			valid_addr = 1;
			rel_addr = addr - memel[i].addr;
		}
		if ((addr >= memel[i].addr_mirror) && (addr < (memel[i].addr_mirror + memel[i].length)) && (memel[i].valid == 1))
		{
			valid_addr = 1;
			rel_addr = addr - memel[i].addr_mirror;
		}
		if (valid_addr == 1)
		{
			i_cache = i;
			*pvalue=memel[i].data[rel_addr];
			return memel[i].status[rel_addr];
		}
		else
		{
		}
	}
	//Restart, cache was missed
	{
		//we have an address and want to set the value
		for (i = 0; i < MAX_memel; i += 1)
		{
			valid_addr = -1;
			if ((addr >= memel[i].addr) && (addr < (memel[i].addr + memel[i].length)) && (memel[i].valid == 1))
			{
				valid_addr = 1;
				rel_addr = addr - memel[i].addr;
			}
			if ((addr >= memel[i].addr_mirror) && (addr < (memel[i].addr_mirror + memel[i].length)) && (memel[i].valid == 1))
			{
				valid_addr = 1;
				rel_addr = addr - memel[i].addr_mirror;
			}
			if (valid_addr == 1)
			{
				i_cache = i;
				*pvalue=memel[i].data[rel_addr];
				return memel[i].status[rel_addr];
			}
			else
			{
			}
		}
	}
	return (0);
}

/* set the value in the memory, call from ihex import*/
/* BYTE_SET_EMPTY, byte is not set */
/* BYTE_SET_CONTENT, byte was directly set */
/* BYTE_SET_PAGE, a byte was set via BYTE_SET_CONTENT, bytes in the page are not set, but will be written. */
int
set_memory_value (unsigned int addr, unsigned char value)
{
	int ret;
	int i, j, valid_addr;
	unsigned int rel_addr;
	static int i_cache = -1;

	ret = -1;
	if (i_cache != -1)
	{
		i = i_cache;
		valid_addr = -1;
		if ((addr >= memel[i].addr) && (addr < (memel[i].addr + memel[i].length)) && (memel[i].valid == 1))
		{
			valid_addr = 1;
			rel_addr = addr - memel[i].addr;
		}
		if ((addr >= memel[i].addr_mirror) && (addr < (memel[i].addr_mirror + memel[i].length)) && (memel[i].valid == 1))
		{
			valid_addr = 1;
			rel_addr = addr - memel[i].addr_mirror;
		}
		if (valid_addr == 1)
		{
			memel[i].was_used = 1;

			if ((memel[i].status[rel_addr] == BYTE_SET_EMPTY) || (memel[i].status[rel_addr] == BYTE_SET_PAGE))
			{
				unsigned int page_begin, page_end;
				//the location is unused
				memel[i].data[rel_addr] = value;
				memel[i].status[rel_addr] = BYTE_SET_CONTENT;
				//apply other pages members with fill value, page size = 0x100 for program flash
				page_begin = rel_addr & ~(memel[i].page_size - 1);
				page_end = rel_addr | (memel[i].page_size - 1);
				for (j = page_begin; j <= page_end; j += 1)
				{
					if (memel[i].status[j] == BYTE_SET_EMPTY)
					{
						memel[i].status[j] = BYTE_SET_PAGE;
						memel[i].data[j] = args_page_value; //the data if byte is used as part of a page, it can be later on overwritten by BYTE_SET_CONTENT and another value.
					}
				}
			}
			i_cache = i;
			return (0);
		}
		else
		{
		}
	}
	//Restart, cache was missed
	{
		//we have an address and want to set the value
		for (i = 0; i < MAX_memel; i += 1)
		{
			valid_addr = -1;
			if ((addr >= memel[i].addr) && (addr < (memel[i].addr + memel[i].length)) && (memel[i].valid == 1))
			{
				valid_addr = 1;
				rel_addr = addr - memel[i].addr;
			}
			if ((addr >= memel[i].addr_mirror) && (addr < (memel[i].addr_mirror + memel[i].length))
					&& (memel[i].valid == 1))
			{
				valid_addr = 1;
				rel_addr = addr - memel[i].addr_mirror;
			}
			if (valid_addr == 1)
			{
				memel[i].was_used = 1;
				if ((memel[i].status[rel_addr] == BYTE_SET_EMPTY) || (memel[i].status[rel_addr] == BYTE_SET_PAGE))
				{
					unsigned int page_begin, page_end;
					//the location is unused
					memel[i].data[rel_addr] = value;
					memel[i].status[rel_addr] = BYTE_SET_CONTENT;
					//apply other pages members with fill value, page size = 0x100 for program flash
					page_begin = rel_addr & ~(memel[i].page_size - 1);
					page_end = rel_addr | (memel[i].page_size - 1);
					for (j = page_begin; j <= page_end; j += 1)
					{
						if (memel[i].status[j] == BYTE_SET_EMPTY)
						{
							memel[i].status[j] = BYTE_SET_PAGE;
							memel[i].data[j] = args_page_value; //the data if byte is used as part of a page, it can be later on overwritten by BYTE_SET_CONTENT and another value.
						}
					}
				}
				i_cache = i;
				return (0);
			}
			else
			{
			}
		}
	}
	return (ret);
}

/* set the value in the memory, call from ihex import*/
/* BYTE_SET_EMPTY */
int
unset_memory_value (unsigned int addr)
{
	int ret;
	int i, j, valid_addr;
	unsigned int rel_addr;
	static int i_cache = -1;

	ret = -1;
	if (i_cache != -1)
	{
		i = i_cache;
		valid_addr = -1;
		if ((addr >= memel[i].addr) && (addr < (memel[i].addr + memel[i].length)) && (memel[i].valid == 1))
		{
			valid_addr = 1;
			rel_addr = addr - memel[i].addr;
		}
		if ((addr >= memel[i].addr_mirror) && (addr < (memel[i].addr_mirror + memel[i].length)) && (memel[i].valid == 1))
		{
			valid_addr = 1;
			rel_addr = addr - memel[i].addr_mirror;
		}
		if (valid_addr == 1)
		{
			memel[i].status[rel_addr] = BYTE_SET_EMPTY;
			i_cache = i;
			return (0);
		}
		else
		{
		}
	}
	//Restart, cache was missed
	{
		{
			for (i = 0; i < MAX_memel; i += 1)
			{
				valid_addr = -1;
				if ((addr >= memel[i].addr) && (addr < (memel[i].addr + memel[i].length)) && (memel[i].valid == 1))
				{
					valid_addr = 1;
					rel_addr = addr - memel[i].addr;
				}
				if ((addr >= memel[i].addr_mirror) && (addr < (memel[i].addr_mirror + memel[i].length))
						&& (memel[i].valid == 1))
				{
					valid_addr = 1;
					rel_addr = addr - memel[i].addr_mirror;
				}
				if (valid_addr == 1)
				{
					memel[i].status[rel_addr] = BYTE_SET_EMPTY;
					i_cache = i;
					return (0);
				}
				else
				{
				}
			}
		}
	}
	return (ret);
}

/* if you want to see the real content of the intel hex this function is very helpfull */
int
analyze_memory_buffer (int list)
{
	int i, j;
	int offs_0, offs_1;
	int banalyzed;
	for (i = 0; i < MAX_memel; i += 1)
	{
		if ((memel[i].was_used != -1) && (memel[i].valid == 1))
		{
			j = 0;
			offs_0 = -1;
			offs_1 = -1;
			banalyzed = 0;
			memel[i].was_used = -1;
			for (int jj = 0; jj < memel[i].blocks; jj += 1)
				memel[i].blocks_used[jj] = 0;
			while (banalyzed == 0)
			{
				if ((memel[i].status[j] != BYTE_SET_EMPTY) && (offs_0 == -1))
					offs_0 = j;
				if ((memel[i].status[j + memel[i].page_size] == BYTE_SET_EMPTY) && (offs_0 != -1) && (offs_1 == -1))
					offs_1 = j + memel[i].page_size - 1;

				if (memel[i].status[j] != BYTE_SET_EMPTY)
					memel[i].blocks_used[j / (memel[i].length/ memel[i].blocks)] = 1;
				if ((offs_0 != -1) && (offs_1 != -1))
				{
					memel[i].was_used = 1;
					if (list == 1)
					{
						printf (
								"Region Used=%3d Addr=0x%8.8X Addr_mirror=0x%8.8X length=0x%8.8X from=0x%8.8X to=0x%8.8X \n",
								i, memel[i].addr, memel[i].addr_mirror, memel[i].length, offs_0 + memel[i].addr,
								offs_1 + memel[i].addr);
					}
					debug_printf("Region Used=%d Addr=%8.8X Addr_mirror=%8.8X length=%8.8X from=%8.8X to=%8.8X \n", i,
							memel[i].addr, memel[i].addr_mirror, memel[i].length, offs_0 + memel[i].addr,
							offs_1 + memel[i].addr);
					debug_printf("Blocks ");
					for (int jj = 0; jj < memel[i].blocks; jj += 1)
					{
						if (memel[i].blocks_used[jj] != 0)
						{
							debug_printf("+");
						}
						else
						{
							debug_printf("-");
						}
					}
					debug_printf("\n");
					offs_0 = -1;
					offs_1 = -1;
				}
				j += memel[i].page_size;
				if (j >= (memel[i].length - memel[i].page_size))
				{
					if (offs_0 != -1)
					{
						memel[i].was_used = 1;
						offs_1 = memel[i].length - 1;
						if (list == 1)
						{
							printf (
									"Region Used=%3d Addr=0x%8.8X Addr_mirror=0x%8.8X length=0x%8.8X from=0x%8.8X to=0x%8.8X \n",
									i, memel[i].addr, memel[i].addr_mirror, memel[i].length, offs_0 + memel[i].addr,
									offs_1 + memel[i].addr);
						}
						debug_printf("Region Used=%d Addr=%8.8X Addr_mirror=%8.8X length=%8.8X from=%8.8X to=%8.8X \n", i,
								memel[i].addr, memel[i].addr_mirror, memel[i].length, offs_0 + memel[i].addr,
								offs_1 + memel[i].addr);
						debug_printf("Blocks ");
						for (int jj = 0; jj < memel[i].blocks; jj += 1)
						{
							if (memel[i].blocks_used[jj] != 0)
							{
								debug_printf("+");
							}
							else
							{
								debug_printf("-");
							}
						}
						debug_printf("\n");
					}
					banalyzed = 1;
				}
			}
		}
	}
	if (list == 1) printf("\n");
	for (i = 0; i < MAX_memel; i += 1)
	{
		if ((memel[i].was_used != -1) && (memel[i].valid == 1))
		{
			if (list == 1)
			{
				printf (
						"Region Used=%3d Addr=0x%8.8X Addr_mirror=0x%8.8X length=0x%8.8X blocks=%3d block_len=%8.8x\n",
						i, memel[i].addr, memel[i].addr_mirror, memel[i].length,memel[i].blocks,memel[i].length/memel[i].blocks);

				printf("blocks -> ");
				for (int jj = 0; jj < memel[i].blocks; jj += 1)
				{
					if (memel[i].blocks_used[jj] != 0)
					{
						printf("+");
					}
					else
					{
						printf("-");
					}
				}
				printf("\n");
			}
		}
	}
	return (0);
}

/* insert a memory element */
int
insert_memory_buffer (int i, unsigned int addr, unsigned int addr_mirror, unsigned int length, unsigned int page_size,
		char memtype, unsigned int base_pfi, unsigned int base_cpu, int blocks)
{
	int j;
	memel[i].length = length;
	if (length > 0x80000)
	{
		printf ("Memory Regions should not be bigger than 512k\n");
		//if you need more memory just split the bigger memory into several 512k regions
		exit (1);
	}
	memel[i].addr = addr;
	memel[i].addr_mirror = addr_mirror;
	memel[i].page_size = page_size;
	memel[i].data = (unsigned char*) malloc (memel[i].length);
	memel[i].status = (char*) malloc (memel[i].length);
	memel[i].blocks = blocks;
	if ((memel[i].length % memel[i].blocks) !=0)
	{
		printf("Error: memory element can only have blocks with length=%8.8x blocks==0 length=%8.8x block_length=%8.8x",memel[i].length,memel[i].length/memel[i].blocks);
	}
	memel[i].blocks_used= (int*) malloc (memel[i].blocks*4);
	for (j = 0; j < memel[i].blocks; j += 1)
		memel[i].blocks_used[j] = 0;
	if (memel[i].data == NULL)
		printf ("MALLOC Issue\n");
	if (memel[i].status == NULL)
		printf ("MALLOC Issue\n");
	//fill status with invalid
	for (j = 0; j < memel[i].length; j += 1)
		memel[i].status[j] = BYTE_SET_EMPTY;
	memel[i].valid = 1;
	memel[i].was_used = -1;
	memel[i].memtype = memtype;
	memel[i].specific = 0;
	memel[i].base_pfi = base_pfi;
	memel[i].base_cpu = base_cpu;
	//  for (j = 0; j < 32; j += 1)
	//    memel[i].sectors_used[j] = -1;
	return (0);
}

int init_flash_TC3xx(int sectors_512k)
{
	int i, id;
	int ret;
	id=0;
	ret |= insert_memory_buffer (id++, 0xAF400000, 0xAF400000, 0x6000, 0x20,MEMTYPE_UCB,0, 0,0x6000/0x200);
	for (i = 0; i < 6; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0000000 + i * 0x80000, 0x80000000 + i * 0x80000, 0x80000, 0x100,MEMTYPE_PFLASH,0xa8080000, 0xF8800000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 6; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0300000 + i * 0x80000, 0x80300000 + i * 0x80000, 0x80000, 0x100,MEMTYPE_PFLASH,0xa8380000, 0xF8820000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 6; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0600000 + i * 0x80000, 0x80600000 + i * 0x80000, 0x80000, 0x100,MEMTYPE_PFLASH,0xa8680000, 0xF8840000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 6; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0900000 + i * 0x80000, 0x80900000 + i * 0x80000, 0x80000, 0x100,MEMTYPE_PFLASH,0xa8980000, 0xF8860000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 6; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0C00000 + i * 0x80000, 0x80C00000 + i * 0x80000, 0x80000, 0x100,MEMTYPE_PFLASH,0xa8C80000, 0xF8880000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 2; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0F00000 + i * 0x80000, 0x80F00000 + i * 0x80000, 0x80000, 0x100,MEMTYPE_PFLASH,0xa8F80000, 0xF88C0000,32);
		if (id==sectors_512k) return (ret);
	}
	return (ret);
}

int init_flash_TC4xx(int sectors_512k)
{
	int i, id;
	int ret;

	id=0;
	ret |= insert_memory_buffer (id++, 0xAE400000, 0xAE400000, 0x14000, 0x20,MEMTYPE_UCB,0, 0,0x14000/0x800);
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0000000 + i * 0x80000, 0x80000000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8410000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0200000 + i * 0x80000, 0x80200000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8418000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0400000 + i * 0x80000, 0x80400000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8450000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0600000 + i * 0x80000, 0x80600000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8458000,32);
		if (id==sectors_512k) return (ret);
	}

	for (i = 0; i < 2; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0800000 + i * 0x80000, 0x80800000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8490000,32);
		if (id==sectors_512k) return (ret);
	}

	for (i = 0; i < 2; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0900000 + i * 0x80000, 0x80900000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8498000,32);
		if (id==sectors_512k) return (ret);
	}

	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0A00000 + i * 0x80000, 0x80A00000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF84D0000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0C00000 + i * 0x80000, 0x80C00000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF84D8000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA0E00000 + i * 0x80000, 0x80E00000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8510000,32);
		if (id==sectors_512k) return (ret);
	}
	for (i = 0; i < 4; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA1000000 + i * 0x80000, 0x81000000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8518000,32);
		if (id==sectors_512k) return (ret);
	}

	for (i = 0; i < 2; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA1200000 + i * 0x80000, 0x81200000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8550000,32);
		if (id==sectors_512k) return (ret);
	}

	for (i = 0; i < 2; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA1300000 + i * 0x80000, 0x81300000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8558000,32);
		if (id==sectors_512k) return (ret);
	}
    //CS
	for (i = 0; i < 2; i += 1)
	{
		ret |= insert_memory_buffer (id++, 0xA4000000 + i * 0x80000, 0x84000000 + i * 0x80000, 0x80000, 0x200,MEMTYPE_PFLASH,0, 0xF8590000,32);
		if (id==sectors_512k) return (ret);
	}
	return (ret);
}

int
init_memory_buffers (int mode)
{
	int i, id;
	int ret;
	//free up the things
	for (i = 0; i < MAX_memel; i += 1)
	{
		memel[i].valid = -1;
		memel[i].was_used = -1;
		if (memel[i].data != NULL)
			free (memel[i].data);
		if (memel[i].status != NULL)
			free (memel[i].status);
		if (memel[i].blocks_used != NULL)
			free (memel[i].blocks_used);
	}

	//the flashing mode
	if (mode == 1)
	{
		ret = 0;
		id = 0;

		if (device_tc3xx())
		{
		//here you have to declare the available memory map
		//best way is to ask for the id of the connected board and then fill the buffers accordingly
		//TC375 has 6MB 12 x 512k= 12 x 32 x 16kByte
		//TC397 has 16MB 32 x 512k = 32 x 32 x 16Kbyte
		unsigned int flash_512k_sectors;
		debug_printf("Chip_ID-> %8.8x \n",chip_id);
			switch ((chip_id>>24) & 0xF)
			{
			case 2:   flash_512k_sectors=2; break;
			case 3:   flash_512k_sectors=3; break;
			case 4:   flash_512k_sectors=4; break;
			case 5:   flash_512k_sectors=5; break;
			case 6:   flash_512k_sectors=6; break;
			case 7:   flash_512k_sectors=8; break;
			case 8:   flash_512k_sectors=10; break;
			case 9:   flash_512k_sectors=12; break;
			case 0xA: flash_512k_sectors=14; break;
			case 0xB: flash_512k_sectors=16; break;
			case 0xC: flash_512k_sectors=20; break;
			case 0xD: flash_512k_sectors=24; break;
			case 0xE: flash_512k_sectors=28; break;
			case 0xF: flash_512k_sectors=32; break;
			default:
			{
				printf("Unknown Flash Size %2.2x as part of Chip_id %8.8x \n",((chip_id>>24) & 0xF),chip_id);
				flasher_exit(1);
			}
			}
			init_flash_TC3xx(flash_512k_sectors);
			return (ret);
		}
		if (device_tc4xx())
		{
		unsigned int flash_512k_sectors;

		debug_printf("Chip_ID-> %8.8x \n",chip_id);
			switch ((chip_id>>11) & 0xF)
			{
			case 2:   flash_512k_sectors=6; break;
			case 3:   flash_512k_sectors=8; break;
			case 4:   flash_512k_sectors=10; break;
			case 5:   flash_512k_sectors=12; break;
			case 6:   flash_512k_sectors=16; break;
			case 8:   flash_512k_sectors=24; break;
			case 9:   flash_512k_sectors=32; break;
			case 0xA: flash_512k_sectors=40; break;
			case 0xB: flash_512k_sectors=48; break;
			default:
			{
				printf("Unknown Flash Size %2.2x as part of Chip_id %8.8x \n",((chip_id>>24) & 0xF),chip_id);
				flasher_exit(1);
			}
			}
			init_flash_TC4xx(flash_512k_sectors);
			return (ret);
		}

	}
	//bootloader mode
	if (mode == 0)
	{
		ret = 0;
		id = 0;
		ret |= insert_memory_buffer (id++, 0x70000000, 0x70000000, 0x28000, 0x100,
				MEMTYPE_RAM,
				0, 0,1);
		return (ret);
	}

	return 1;
}

static inline int
scanbyte (char *theline, int *res)
{
	int val4bit;
	if (!isxdigit (theline[0]))
		return 0;
	if (!isxdigit (theline[1]))
		return 0;
	int val = 0;
	if (theline[0] >= '0' && theline[0] <= '9')
		val4bit = theline[0] - '0';
	else if (theline[0] >= 'a' && theline[0] <= 'f')
		val4bit = theline[0] - 'a' + 10;
	else if (theline[0] >= 'A' && theline[0] <= 'F')
		val4bit = theline[0] - 'A' + 10;
	// shift 4 to make space for new digit, and add the 4 bits of the new digit
	val = (val << 4) | (val4bit & 0xF);
	if (theline[1] >= '0' && theline[1] <= '9')
		val4bit = theline[1] - '0';
	else if (theline[1] >= 'a' && theline[1] <= 'f')
		val4bit = theline[1] - 'a' + 10;
	else if (theline[1] >= 'A' && theline[1] <= 'F')
		val4bit = theline[1] - 'A' + 10;
	// shift 4 to make space for new digit, and add the 4 bits of the new digit
	val = (val << 4) | (val4bit & 0xF);
	*res = val;
	return 1;
}

static inline int
scanshort (char *theline, unsigned int *res)
{
	int val4bit;
	if (!isxdigit (theline[0]))
		return 0;
	if (!isxdigit (theline[1]))
		return 0;
	if (!isxdigit (theline[2]))
		return 0;
	if (!isxdigit (theline[3]))
		return 0;
	int val = 0;
	if (theline[0] >= '0' && theline[0] <= '9')
		val4bit = theline[0] - '0';
	else if (theline[0] >= 'a' && theline[0] <= 'f')
		val4bit = theline[0] - 'a' + 10;
	else if (theline[0] >= 'A' && theline[0] <= 'F')
		val4bit = theline[0] - 'A' + 10;
	// shift 4 to make space for new digit, and add the 4 bits of the new digit
	val = (val << 4) | (val4bit & 0xF);
	if (theline[1] >= '0' && theline[1] <= '9')
		val4bit = theline[1] - '0';
	else if (theline[1] >= 'a' && theline[1] <= 'f')
		val4bit = theline[1] - 'a' + 10;
	else if (theline[1] >= 'A' && theline[1] <= 'F')
		val4bit = theline[1] - 'A' + 10;
	// shift 4 to make space for new digit, and add the 4 bits of the new digit
	val = (val << 4) | (val4bit & 0xF);
	if (theline[2] >= '0' && theline[2] <= '9')
		val4bit = theline[2] - '0';
	else if (theline[2] >= 'a' && theline[2] <= 'f')
		val4bit = theline[2] - 'a' + 10;
	else if (theline[2] >= 'A' && theline[2] <= 'F')
		val4bit = theline[2] - 'A' + 10;
	// shift 4 to make space for new digit, and add the 4 bits of the new digit
	val = (val << 4) | (val4bit & 0xF);
	if (theline[3] >= '0' && theline[3] <= '9')
		val4bit = theline[3] - '0';
	else if (theline[3] >= 'a' && theline[3] <= 'f')
		val4bit = theline[3] - 'a' + 10;
	else if (theline[3] >= 'A' && theline[3] <= 'F')
		val4bit = theline[3] - 'A' + 10;
	// shift 4 to make space for new digit, and add the 4 bits of the new digit
	val = (val << 4) | (val4bit & 0xF);
	*res = val;
	return 1;
}

//allfunctions below are intelhex converstion  routines.
//dirty hack to understand ihex extended
int
parse_hex_line_addr (char *theline, int bytes[], unsigned int *addr, int *num, int *code)
{
	int sum, len, cksum;
	char *ptr;
	int lenline;
	lenline = strlen (theline);
	*num = 0;
	if (theline[0] != ':')
		return 0;
	if (lenline < 11)
		return 0;
	ptr = theline + 1;
	if (!scanbyte (ptr, &len))
		return 0;
	ptr += 2;
	if (len != 2)
		return 0;
	if (lenline < (11 + (len * 2)))
		return 0;
	if (!scanshort (ptr, addr))
		return 0;
	ptr += 4;
	if (*addr != 0)
		return 0;
	if (!scanbyte (ptr, code))
		return 0;
	ptr += 2;
	if (*code != 4)
		return 0;
	sum = (len & 255) + ((*addr >> 8) & 255) + (*addr & 255) + (*code & 255);
	while (*num != len)
	{
		if (!scanbyte (ptr, &bytes[*num]))
			return 0;
		ptr += 2;
		sum += bytes[*num] & 255;
		(*num)++;
		if (*num >= 256)
			return 0;
	}
	*addr = bytes[0] * 256 + bytes[1];
	*addr = *addr << 16;
	if (!scanbyte (ptr, &cksum))
		return 0;
	if (((sum & 255) + (cksum & 255)) & 255)
		return 0; /* checksum error */
		return 1;
}

int
parse_hex_line (char *theline, int bytes[], unsigned int *addr, int *num, int *code)
{
	int sum, len, cksum;
	char *ptr;
	int lenline;
	lenline = strlen (theline);
	*num = 0;
	if (theline[0] != ':')
		return 0;
	if (lenline < 11)
		return 0;
	ptr = theline + 1;
	if (!scanbyte (ptr, &len))
		return 0;
	ptr += 2;
	if (lenline < (11 + (len * 2)))
		return 0;
	if (!scanshort (ptr, addr))
		return 0;
	ptr += 4;
	if (!scanbyte (ptr, code))
		return 0;
	ptr += 2;
	sum = (len & 255) + ((*addr >> 8) & 255) + (*addr & 255) + (*code & 255);
	while (*num != len)
	{
		if (!scanbyte (ptr, &bytes[*num]))
			return 0;
		ptr += 2;
		sum += bytes[*num] & 255;
		(*num)++;
		if (*num >= 256)
			return 0;
	}
	if (!scanbyte (ptr, &cksum))
		return 0;
	if (((sum & 255) + (cksum & 255)) & 255)
		return 0; /* checksum error */
		return 1;
}

void print_sections(std::vector<elf_parser::section_t> &sections);
void print_segments(std::vector<elf_parser::segment_t> &segments);

void
load_file_elf (char *filename, int verbose, int check_hex)
{
	int cks_hex=0;
	int cnt_hex=0;

	if (check_hex!=0)
	{
	int i;
	//we have an address and want to set the value
	for (i = 0; i < MAX_memel; i += 1)
	{
		for (int jj=0; jj<memel[i].length; jj+=1)
		{
			if (memel[i].status[jj] == BYTE_SET_CONTENT)
				{
				cks_hex+=memel[i].data[jj];
				cnt_hex+=1;
				}
		}
	}
	}

    std::string program((std::string)filename);
    elf_parser::Elf_parser elf_parser(program);
//    std::vector<elf_parser::section_t> secs = elf_parser.get_sections();
//    print_sections(secs);
    std::vector<elf_parser::segment_t> segs = elf_parser.get_segments();
    uint8_t *mem;
    mem=elf_parser.get_memory_map();
	int cks_elf=0;
	int cnt_elf=0;
    for (auto &segment : segs) {
        debug_printf("   %-8s 0x%08" PRIx32 " 0x%08" PRIx32 " 0x%08" PRIx32 "",
                segment.segment_type.c_str(),
                segment.segment_offset,
                segment.segment_virtaddr,
                segment.segment_physaddr);

        debug_printf("   %-8s 0x%08" PRIx32 " 0x%08" PRIx32 " %-5s %-5" PRIx32 "\n", "",
                segment.segment_filesize,
                segment.segment_memsize,
                segment.segment_flags.c_str(),
                segment.segment_align);
        if (segment.segment_filesize==0) continue;
        if (segment.segment_offset==0) continue;
        {
        	unsigned int addr=segment.segment_physaddr;
        	for (int ii=segment.segment_offset; ii<(segment.segment_offset+segment.segment_memsize); )
        	{
        		if (check_hex!=0)
        		{
        			unsigned char value;
        			if (get_memory_value(addr,&value)==0)
        			{
        				printf("Addr %8.8x not set as part of elf-file\n",addr);
        				flasher_exit(1);
        			}
        			if (mem[ii]!=value)
        			{
        				printf("Addr %8.8x elf-file %2.2x not equal to hex-file %2.2x\n",addr,value,mem[ii]);
        				flasher_exit(1);
        			}
        		}
        		set_memory_value(addr,mem[ii]);
        		cks_elf+=mem[ii];
        		cnt_elf+=1;
        		ii+=1;
        		addr+=1;
        	}
        }
    }
	if (check_hex!=0)
	{
		if (cks_elf!=cks_hex)
		{
			printf("Checksum elf-file %8.8x (bytes %d) not equal to hex-file %8.8x (bytes %d) \n",cks_elf,cnt_elf,cks_hex,cnt_hex);
			flasher_exit(1);
		}
	}
	printf ("::Loading ELF file .......... (Pass)\n");
}

void print_sections(std::vector<elf_parser::section_t> &sections) {
    printf("  [Nr] %-8s %-8s %-8s %30s\n", "Name", "Type", "Address", "Offset");
    printf("       %-8s %-8s %5s ",
                    "Size", "EntSize", "Align");

    for (auto &section : sections) {
        printf("  [%4d] %-30s %-8s %08" PRIx32 " %08" PRIx32 "",
            section.section_index,
            section.section_name.c_str(),
            section.section_type.c_str(),
            section.section_addr,
            section.section_offset);

        printf("       %08zx %08" PRIx32 " %5" PRIu32 "\n",
            section.section_size,
            section.section_ent_size,
            section.section_addr_align);
    }
}

void print_segments(std::vector<elf_parser::segment_t> &segments) {
    printf("  %-8s  %-8s   %-8s   %s\n", "Type", "Offset", "VirtAddr", "PhysAddr");
    printf("  %-8s  %-8s   %-8s  %6s %5s\n", " ", "FileSiz", "MemSiz", "Flags", "Align");

    for (auto &segment : segments) {
        printf("   %-8s 0x%08" PRIx32 " 0x%08" PRIx32 " 0x%08" PRIx32 "",
                segment.segment_type.c_str(),
                segment.segment_offset,
                segment.segment_virtaddr,
                segment.segment_physaddr);

        printf("   %-8s 0x%08" PRIx32 " 0x%08" PRIx32 " %-5s %-5" PRIx32 "\n", "",
                segment.segment_filesize,
                segment.segment_memsize,
                segment.segment_flags.c_str(),
                segment.segment_align);
//        uint8_t *mem;
//        mem=get_memory_map();
//        mem=(unsigned char*)(m_mmap_program + segment.segment_offset);
//        for (int ii=0; ii<segment.segment_memsize;ii+=1)
//        {
//        	printf("%8.8x ",mem[ii]);
//        	if ((ii%8)==0) printf("\n");
//        }
//    	printf("\n");
    }
}


/* loads an intel hex file into the global memory[] array */
/* filename is a string of the file to be opened */

void
load_file_hex (char *filename, int verbose)
{
	char line[1000];
	FILE *fin;
	int n, status, bytes[256];
	unsigned int addr;
	unsigned int addr_offs;
	unsigned int tmp_addr_offs;
	int lenline;
	int i, total = 0, lineno = 1;
	addr_offs = 0;
	if (strlen (filename) == 0)
	{
		printf ("   Can't load a file without the filename.");
		exit (1);
		return;
	}
	fin = fopen (filename, "r");
	if (fin == NULL)
	{
		printf ("   Can't open file '%s' for reading.\n", filename);
		exit (1);
		return;
	}
	while (!feof (fin) && !ferror (fin))
	{
		line[0] = '\0';
		char *res = fgets (line, 1000, fin);
		lenline = strlen (line);
		if (line[lenline - 1] == '\n')
			line[lenline - 1] = '\0';
		if (line[lenline - 1] == '\r')
			line[lenline - 1] = '\0';
		if (parse_hex_line_addr (line, bytes, &tmp_addr_offs, &n, &status))
		{
			if (status == 4)
			{ /* data */
				addr_offs = tmp_addr_offs;
				debug_printf("Changed Address offest to %8.8X \n", addr_offs);
			}
		}

		if (parse_hex_line (line, bytes, &addr, &n, &status))
		{
			if (status == 0)
			{ /* data */
				for (i = 0; i <= (n - 1); i++)
				{
					unsigned char value;
					int ret;
					value = bytes[i] & 255;
					ret = set_memory_value (addr + addr_offs, value);
					if ((ret == -1) && (args_map == 1))
					{
						printf ("Error! Could not map address addr=%8.8x (base=%8.8x + offs=%8.8x) \n", addr + addr_offs,
								addr, addr_offs);
						printf ("Hex File (lineno=%d)-> %s\n", lineno, line);
						exit (1);
					}
					total++;
					addr++;
				}
			}
			if (status == 1)
			{ /* end of file */
				fclose (fin);
				debug_printf("IHEX %s Loaded %d bytes \n", filename, total);
				if (verbose==0) printf ("::Loading HEX file .......... (Pass)\n");
				return;
			}
			if (status == 2)
				; /* begin of file */
		}
		else
		{
			printf ("   Error: '%s', line: %d\n", filename, lineno);
		}
		lineno++;
	}
}

/* the command string format is "S begin end filename" where */
/* "begin" and "end" are the locations to dump to the intel */
/* hex file, specified in hexidecimal. */

void
save_file (char *command)
{
	int begin, end, addr;
	char *ptr, filename[200];
	FILE *fhex;

	ptr = command + 1;
	while (isspace (*ptr))
		ptr++;
	if (*ptr == '\0')
	{
		printf ("   Must specify address range and filename\n");
		return;
	}
	if (sscanf (ptr, "%x%x%s", &begin, &end, filename) < 3)
	{
		printf ("   Invalid addresses or filename,\n");
		printf ("    usage: S begin_addr end_addr filename\n");
		printf ("    the addresses must be hexidecimal format\n");
		return;
	}
	begin &= 65535;
	end &= 65535;
	if (begin > end)
	{
		printf ("   Begin address must be less than end address.\n");
		return;
	}
	fhex = fopen (filename, "w");
	if (fhex == NULL)
	{
		printf ("   Can't open '%s' for writing.\n", filename);
		return;
	}
	for (addr = begin; addr <= end; addr++)
		hexout (fhex, memory[addr], addr, 0);
	hexout (fhex, 0, 0, 1);
	printf ("Memory %04X to %04X written to '%s'\n", begin, end, filename);
}

/* produce intel hex file output... call this routine with */
/* each byte to output and it's memory location.  The file */
/* pointer fhex must have been opened for writing.  After */
/* all data is written, call with end=1 (normally set to 0) */
/* so it will flush the data from its static buffer */

#define MAXHEXLINE 32	/* the maximum number of bytes to put in one line */

void
hexout (FILE *fhex, int byte, int memory_location, int end)
{
	static int byte_buffer[MAXHEXLINE];
	static int last_mem, buffer_pos, buffer_addr;
	static int writing_in_progress = 0;
	int i, sum;

	if (!writing_in_progress)
	{
		/* initial condition setup */
		last_mem = memory_location - 1;
		buffer_pos = 0;
		buffer_addr = memory_location;
		writing_in_progress = 1;
	}

	if ((memory_location != (last_mem + 1)) || (buffer_pos >= MAXHEXLINE) || ((end) && (buffer_pos > 0)))
	{
		/* it's time to dump the buffer to a line in the file */
		fprintf (fhex, ":%02X%04X00", buffer_pos, buffer_addr);
		sum = buffer_pos + ((buffer_addr >> 8) & 255) + (buffer_addr & 255);
		for (i = 0; i < buffer_pos; i++)
		{
			fprintf (fhex, "%02X", byte_buffer[i] & 255);
			sum += byte_buffer[i] & 255;
		}
		fprintf (fhex, "%02X\n", (-sum) & 255);
		buffer_addr = memory_location;
		buffer_pos = 0;
	}

	if (end)
	{
		fprintf (fhex, ":00000001FF\n"); /* end of file marker */
		fclose (fhex);
		writing_in_progress = 0;
	}

	last_mem = memory_location;
	byte_buffer[buffer_pos] = byte & 255;
	buffer_pos++;
}


