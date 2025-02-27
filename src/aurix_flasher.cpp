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

#include "tas_client_rw.h"
#include "tas_utils.h"
#include "tas_device_family.h"

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


#if linux

#include <sys/time.h>

#include <ctype.h>

#endif

//the interfacing functions towards flash_tool_ihex.cpp
//this file is a copy of tas_api_demo_main.cpp, I commented all unneeded printfs out.
//please check for more information in flash_tool_ihex.cpp
extern int target_download_init(CTasClientRw *client);
extern int target_download_ram(CTasClientRw *client, char *pname);
extern int target_download_flash_double (CTasClientRw *client, char *pname_hex, char *pname_elf, int emul);
extern int target_perf_ram (CTasClientRw *client);
extern void println_time(const char* info);
unsigned int chip_id;
unsigned int jtag_id;
char *args_filename_ihex;
char *args_filename_elf;
int args_start_reset;
int args_opt_flash;
int args_frequency;
int args_page_value;
int args_mem_list;
int args_map;
int args_ucb;
int args_erase; //0=is erase used, 1=all, 2=off
int args_ver; //0=is erase used, 1=all, 2=off
int args_log;
int args_id;
int args_id_list;

char iflash_code[1024];

#if defined(_WIN32)
	SYSTEMTIME flasher_time_end;
	SYSTEMTIME flasher_time_start;
	LONG flasher_time_delta_ms;
#endif

#if defined(linux)
	struct timeval flasher_time_end;
	struct timeval flasher_time_start;
	uint64_t  flasher_time_delta_ms;
#endif

#if defined(_WIN32)
LONG delta_ms(SYSTEMTIME time_start,SYSTEMTIME time_end);
#endif

#if defined(linux)
uint64_t delta_ms(struct timeval time_start,struct timeval time_end);
#endif

void flasher_exit(int error)
{
#if defined(_WIN32)
	GetSystemTime(&flasher_time_end);
#endif
#if defined(linux)
	gettimeofday(&flasher_time_end, NULL);
#endif
	printf("Overall time: %ld ms\n", delta_ms(flasher_time_start,flasher_time_end));
	fflush(stdout);
	if (error==0)
		printf("AURIXFlasher Exit Status: Pass\n");
	else
		printf("AURIXFlasher Exit Status: Fail\n");
	exit(error);
}


void devices(void)
{
	printf("This version supports the following devices:\n");
	printf("TC4Dx A step\n");
	printf("TC39x B step\n");
	printf("TC39x B step Extended / ADAS\n");
	printf("TC38x A step\n");
	printf("TC37x A step\n");
	printf("TC37x A step Extended / ADAS\n");
	printf("TC36x A step\n");
	printf("TC35x A step Extended / ADAS\n");
	printf("TC33x A step\n");
	printf("TC33x A step Extended / ADAS\n");
}

void help(void)
{

	printf("Usage: AURIXFlasher.exe <COMMAND> [<COMMAND>] [...]\n");
	printf("<COMMAND>            List of available commands:\n");
	printf("  -l                 List of devices supported (-list)\n");
	printf("  -hex   <file>      Specify flash memory content in INTEL HEX format, use \"file\" if spaces are in\n");
	printf("  -elf   <file>      Specify flash memory content in elf-file format, use \"file\" if spaces are in\n"); 	printf("  -freq  <number>    Specify the frequency Hz for DAP/JTAG as decimal\n");
	printf("         <number>    between 1000000...20000000 (1MHz...20MHz)\n");
	printf("         <number>    (default) 150000000 (15MHz)\n");
	printf("  -erase <arg>       Specify flash memory erasing options\n");
	printf("         <arg>       if 'on': Erase used flash memory only (default)\n");
	printf("         <arg>       if 'all': Erase all flash memory - overrules -opt on\n");
	printf("         <arg>       if 'off': Disable erase operation\n");
	printf("  -start <arg>       Specify task at the end of the process\n");
	printf("         <arg>       if 'on': Start the device by performing a reset (default)\n");
	printf("         <arg>       if 'off': Leave the device in halt state\n");
	printf("  -opt   <arg>       Optimizes the flashing procedure\n");
	printf("         <arg>       if 'on': Do not erase & program areas with identical values (default)\n");
	printf("         <arg>       if 'off': Turn off the optimization\n");
	printf("  -page  <number>    Specify page byte filling for undefined values\n");
	printf("         <number>    between 00..FF as hex value\n");
	printf("         <number>    (default) 00 \n");
	printf("  -mem   <arg>       List memory usage of the device\n");
	printf("         <arg>       if 'on': list\n");
	printf("         <arg>       if 'off': do not list (default)\n");
	printf("  -map   <arg>       Abort if loaded data is not fitting to memory map of the device\n");
	printf("         <arg>       if 'on': abort (default)\n");
	printf("         <arg>       if 'off': do not abort\n");
	printf("  -ucb   <arg>       Specify UCB options\n");
	printf("         <arg>       if 'on': Enable programmig of BMHD into UCB memory (WARNING: wrong BMHD may brick your device!)\n");
	printf("         <arg>       if 'off': Disable programming of BMHD into UCB memory (default)\n");
	printf("  -gui   <arg>       GUI Usage\n");
	printf("         <arg>       if 'on': not supported\n");
	printf("         <arg>       if 'off': Supported (default)\n");
	printf("  -id    <number>    Board id which TAS has to use\n");
	printf("         <arg>       'list' list the board id which connected to TAS\n");
	printf("  -ver   <arg>       Specify flash memory post verification options\n");
	printf("         <arg>       if 'on': Enable Flash memory verify operation\n");
	printf("         <arg>       if 'off: Disable Flash memory verify operation (default)\n");
	printf("  -log   <arg>       Generates Logging Information (huge amount of log) on stdout\n");
	printf("         <arg>       if 'on': Enable Logging\n");
	printf("         <arg>       if 'off: Disable Logging (default)\n");

	/* The original command options */
#if 0
	printf("Usage: AURIXFlasher.exe <COMMAND> [<COMMAND>] [...]\n");
	printf("<COMMAND>           List of available commands:\n");
	printf("  -l                List of devices supported (-list)\n"); <--implemented
	printf("  -hex <file>       Specify flash memory content in INTEL HEX format\n"); <--implemented
	printf("  -elf <file>       Specify flash memory content in elf-file format\n"); <--not implemented
	printf("  -erase <arg>      Specify flash memory erasing options (-e)\n"); <--not implemented
	printf("         <arg>      if 'on': Erase used flash memory only (default)\n");
	printf("         <arg>      if 'all': Erase all flash memory\n");
	printf("         <arg>      if 'off': Disable erase operation\n");
	printf("  -ver <arg>        Specify flash memory post verification options (-v)\n"); <--not implemented
	printf("      <arg>         if 'on': Enable Flash memory verify operation\n");
	printf("      <arg>         if 'off: Disable Flash memory verify operation (default)\n");
	printf("  -ucb  <arg>       Specifiy UCB options for TC3xx devices (-bmhd)\n"); <--not implemented
	printf("       <arg>        if 'on': Enable programmig of BMHD into UCB memory (WARNING: wrong BMHD may brick your device!)\n");
	printf("       <arg>        if 'off': Disable programming of BMHD into UCB memory (default)\n");
	printf("  -connect <arg>     Specify the connection type to the device\n"); <--not implemented
	printf("          <arg>     if '0': Connect device with a 'hot attach' (WARNING: the device must be halted prior the flashing operation!)\n");
	printf("          <arg>     if '6': Connect device by performing a reset&halt (default)\n");
	printf("  -start <arg>      Specify task at the end of the process\n"); <-- implemented
	printf("        <arg>       if 'on': Start the device by performing a reset (default)\n");
	printf("        <arg>       if 'off': Leave the device in halt state\n");
	printf("  -log <file.xml>   Save a log file into <file.xml> in XML format that contains more detailed information about errors and warnings.\n"); <--not implemented
#endif
}

int process_args(int argc, char* argv[])
{
	int ii;
	int pass=1;
	args_filename_ihex=NULL;
	args_start_reset=1;
	args_frequency=15000000;
	args_opt_flash=1;
	args_page_value=0;
	args_mem_list=0;
	args_map=1;
	args_ucb=0;
	args_erase=0;
	args_ver=0;
	args_log=0;
	args_id_list=0;
	args_id=0;
	strcpy(&iflash_code[0],dirname(argv[0]));
	if (argc<=1)
	{
		help();
		exit(0);
	}
	ii=1;
	while (ii<argc)
	{
		if (strcmp(argv[ii],"-l")==0)
		{
			devices();
			exit(0);
		}
		if ((strcmp(argv[ii],"-hex")==0) && ((ii+1)<=argc))
		{
			args_filename_ihex=argv[ii+1];
			ii+=2;
			continue;
		}
		if ((strcmp(argv[ii],"-id")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"list")==0)
			{
				args_id_list=1;
				ii+=2;
				continue;
			}

			int nr;
			if (sscanf(argv[ii+1],"%d",&nr)==1)
			{
				args_id=nr;
				ii+=2;
				continue;
			}
			printf("Error: -id <number> required\n");
			exit(1);
			continue;
		}
		if ((strcmp(argv[ii],"-elf")==0) && ((ii+1)<=argc))
		{
			args_filename_elf=argv[ii+1];
			ii+=2;
			continue;
		}
		if ((strcmp(argv[ii],"-ver")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_ver=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_ver=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-log")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_log=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_log=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-start")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_start_reset=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_start_reset=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-erase")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_erase=0;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"all")==0)
			{
				args_opt_flash=0; //no optimzation needed
				args_erase=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_opt_flash=0; //no optimzation needed
				args_erase=2;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-opt")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_opt_flash=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_opt_flash=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-gui")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				printf("-gui on is not supported\n");
				exit(1);
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-ucb")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_ucb=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_ucb=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-mem")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_mem_list=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_mem_list=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-map")==0) && ((ii+1)<=argc))
		{
			if (strcmp(argv[ii+1],"on")==0)
			{
				args_map=1;
				ii+=2;
				continue;
			}
			if (strcmp(argv[ii+1],"off")==0)
			{
				args_map=0;
				ii+=2;
				continue;
			}
		}
		if ((strcmp(argv[ii],"-freq")==0) && ((ii+1)<=argc))
		{
			int freq;
			if (sscanf(argv[ii+1],"%d",&freq)==1)
			{
				if ((freq>=1000000) && (freq<=20000000))
				{
					args_frequency=freq;
					ii+=2;
					continue;
				}
			}
			printf("Error: Frequency not in range 1000000 ... 20000000\n");
			exit(1);
		}
		if ((strcmp(argv[ii],"-page")==0) && ((ii+1)<=argc))
		{
			int page_value;
			if (sscanf(argv[ii+1],"%x",&page_value)==1)
			{
				if ((page_value>=0) && (page_value<=255))
				{
					args_page_value=page_value;
					ii+=2;
					continue;
				}
			}
			printf("Error: Page by filling not in range 00 ... FF\n");
			exit(1);
		}
		pass=0;
		break;
	}
    if ((args_id_list==1) && (pass!=0))
    {
      return 0;
    }
	if ((pass!=0) && (args_filename_ihex==NULL) && (args_filename_elf==NULL))
	{
		printf("Error: Specify a input file\n");
		exit(1);
	}
	if (pass==0)
	{
		printf("Error: Could not recognize command line parameters\n");
		help();
		exit(1);
	}

	return 0;
}

//********************************************************************************************************************

int device_tc2xx(void)
{
	if (jtag_id==0x201E9083) return 1; //TC29B
	if (jtag_id==0x501DA083) return 1; //TC27D
	if (jtag_id==0x201E8083) return 1; //TC26B
	if (jtag_id==0x10200083) return 1; //TC23A
	if (jtag_id==0x10201083) return 1; //TC22A
	if (jtag_id==0x10202083) return 1; //TC21A
	return 0;
}

int device_tc3xx(void)
{
	if (jtag_id==0x20205083) return 1; //TC39B
	if (jtag_id==0x10206083) return 1; //TC38
	if (jtag_id==0x10207083) return 1; //TC37
	if (jtag_id==0x10209083) return 1; //TC36
	if (jtag_id==0x1020A083) return 1; //TC35
	if (jtag_id==0x1020B083) return 1; //TC33
	if (jtag_id==0x1020C083) return 1; //TC33x
	if (jtag_id==0x10215083) return 1; //TC3Ex
	return 0;
}

int device_tc4xx(void)
{
	if (jtag_id==0x10225083) return 1; //TC4DA
	return 0;
}


//----------------------------------------------------- Main ---------------------------------------------------------
//********************************************************************************************************************
int main(int argc, char* argv[])
{



#if defined(_WIN32)
	GetSystemTime(&flasher_time_start);
#endif

#if defined(linux)
	gettimeofday(&flasher_time_start, NULL);
#endif
	println_time("Start");
	printf("Volumit AURIX Flasher Software Tool 0.0.0.1, built on %s %s\n",__DATE__, __TIME__);
	process_args(argc,argv);
	// Create an instance of TAS Client RW
	// This is copy and past code
	CTasClientRw clientRw("DemoClientRw");
	// Connect to the server, provide IP address or localhost
	tas_return_et ret; // TAS return value
	ret = clientRw.server_connect("localhost");
	if (ret != TAS_ERR_NONE)
	{
		printf("Failed to connect to the server, %s\n", clientRw.get_error_info());
		// other error processing code
		flasher_exit(1);
	}


	// Print the server info
	//printf("\n");
	const tas_server_info_st* serverInfo = clientRw.get_server_info();
	//printf("Server Info: \n");

	time_t startTime = serverInfo->start_time_us / 1000000;  // Convert to seconds
	char timeStr[20];
	tasutil_get_time_str(startTime, timeStr);
	//printf("Started at %s\n", timeStr);

	//printf("%s V%d.%d (%s)\n", serverInfo->server_name, serverInfo->v_major, serverInfo->v_minor, serverInfo->date);

	// Print the server IP address and its port number
	//printf("Server IP:port: %s:%d\n", clientRw.get_server_ip_addr(), clientRw.get_server_port_num());


	// Print the list of targets connected to the server
	//printf("\n");
	const tas_target_info_st* targets; // list of targets
	uint32_t numTargets; // number of connected targets, updated by the API call
	ret = clientRw.get_targets(&targets, &numTargets);

	if (ret != TAS_ERR_NONE)
	{
		printf("Failed to get the list of targets %s\n", clientRw.get_error_info());
		// other error processing code
		flasher_exit(1);
	}
	//printf("Number of targets: %d\n", numTargets);
	for (uint32_t i = 0; i < numTargets; i++)
	{
		const char* deviceName = tas_get_device_name_str(targets[i].device_type);
		uint32_t deviceIdHash = tasutil_crc32(targets[i].device_id, 16);
		char deviceIdHashStr[TASUTIL_HASH32_STRBUF_SIZE];
		tasutil_hash32_to_str(deviceIdHash, deviceIdHashStr);
		if (args_id_list)
			{
			printf("-id %d -> Target %d: %s %s (%s)\n", i, i, deviceName, deviceIdHashStr, targets[i].identifier);
			}
	}
	if (numTargets==0)
	{
		printf("No Target Connected\n");
		flasher_exit(1);
	}
	if (args_id_list)
	{
		flasher_exit(0);
	}

	// Connect to the first target from the list
	//printf("\n");
	//printf("Connecting to the first target from the list...\n");
	if (numTargets<=args_id)
	{
		printf("The selected target id is not conntected via TAS Id=%d (avail. ids) \n",args_id,numTargets);
		flasher_exit(1);
	}
	ret = clientRw.session_start(targets[args_id].identifier, "DemoSession");
	if (ret != TAS_ERR_NONE)
	{
		printf("Failed to start a session, %s\n", clientRw.get_error_info());
		// other error processing code
		flasher_exit(1);
	}



	// Print con_info
	const tas_con_info_st* conInfo = clientRw.get_con_info();
	const int infoStrBufSize = 4096;
	char infoStr[infoStrBufSize];
	int s = snprintf(infoStr, 16, "TARGET:\n");
	//tasutil_get_con_info_str(conInfo, infoStr + s);
	//printf("%s", infoStr);
	printf("Connected to device... %s\n",conInfo->identifier); //TRICORE can be taken from Chip ID
	chip_id=conInfo->device_id[0];
	jtag_id=conInfo->device_type;

	if (args_log==1)
	{
	printf("device_type %8.8x\n",conInfo->device_type);
	printf("device_id[0] %8.8x\n",conInfo->device_id[0]);
	printf("device_id[1] %8.8x\n",conInfo->device_id[1]);
	printf("device_id[2] %8.8x\n",conInfo->device_id[2]);
	printf("device_id[3] %8.8x\n",conInfo->device_id[3]);
	}


	// Reset the target
	ret = clientRw.device_connect(TAS_CLNT_DCO_RESET_AND_HALT);
	if (ret != TAS_ERR_NONE)
	{
		printf("Failed to reset the device, %s\n", clientRw.get_error_info());
		flasher_exit(1);
		// other error processing code
	}

	//This is the relevant code.
	//All things are handled in flash_tool_ihex.cpp
	println_time("target_download_init Begin");
	target_download_init(&clientRw);
	println_time("target_download_init End");
	println_time("target_download_ram Begin");
	extern char iflash_code[1024];
	if (device_tc3xx())
	  {
#if defined(_WIN32)
	    strcat(&iflash_code[0],"\\flash_TC3xx.hex");
#endif

#if defined(linux)
	    strcat(&iflash_code[0],"/flash_TC3xx.hex");
#endif
	  }
	else if (device_tc2xx())
	  {
	    printf("TC2xx Family not supported -> jtag_id %8.8x \n",jtag_id);
	    flasher_exit(1);
	  }
	else if (device_tc4xx())
	  {
#if defined(_WIN32)
	    strcat(&iflash_code[0],"\\flash_TC4xx.hex");
#endif

#if defined(linux)
	    strcat(&iflash_code[0],"/flash_TC4xx.hex");
#endif
	  }
	else
	  {
	    printf("Unknown Family not supported -> jtag_id %8.8x \n",jtag_id);
	    flasher_exit(1);
	  }


	target_download_ram(&clientRw,&iflash_code[0]);
	//    target_perf_ram(&clientRw); //if you want to check the write performance
	println_time("target_download_ram End");
	println_time("target_download_flash_double Begin");
	target_download_flash_double(&clientRw, args_filename_ihex,args_filename_elf, 0);
	println_time("target_download_flash_double End");

#if 0
	enum { BUF_SIZE = 64 };
	uint32_t rdData[BUF_SIZE], wrData[BUF_SIZE];
	uint32_t addr;
	uint8_t  value8, rdData8;

	const uint32_t baseAddr = 0x70000000;
	if (!tas_device_family_is_aurix(conInfo->device_type))
	{
		printf("The address 0x%8.8X is for AURIX devices. Please modify for other devices.\n", baseAddr);
		// other error processing code
		return -1;  // Fatal
	}

	// Basic read/write operations
	printf("\n");
	printf("Basic read/write operations\n");
	addr = baseAddr;
	printf("\tRead - write - read 1 Byte at address 0x%08X\n", addr);
	tasutil_assert(clientRw.read8(addr, &rdData8));
	printf("Read data: %02X\n", rdData8);
	value8 = 0xAB;
	printf("Write 0x%02X\n", value8);
	tasutil_assert(clientRw.write8(addr, value8));
	tasutil_assert(clientRw.read8(addr, &rdData8));
	printf("Read back data: %02X\n", rdData8);

	printf("\n");
	addr = baseAddr + 1;
	printf("\tRead - write - read 1 Byte at address 0x%08X\n", addr);
	tasutil_assert(clientRw.read8(addr, &rdData8));
	printf("Read data: %02X\n", rdData8);
	value8 = 0xCD;
	printf("Write 0x%02X\n", value8);
	tasutil_assert(clientRw.write8(addr, value8));
	tasutil_assert(clientRw.read8(addr, &rdData8));
	printf("Read back data: %02X\n", rdData8);

	// Reset the target
	tasutil_assert(clientRw.device_connect(TAS_CLNT_DCO_RESET_AND_HALT));

	printf("\n");
	addr = baseAddr;
	printf("\tRead - write - read 4 Bytes at address 0x%08X\n", addr);
	tasutil_assert(clientRw.read32(addr, rdData));
	printf("Read data: %08X\n", rdData[0]);
	wrData[0] = 0xABCDEF09;
	printf("Write 0x%08X\n", wrData[0]);
	tasutil_assert(clientRw.write32(addr, wrData[0]));
	tasutil_assert(clientRw.read32(addr, rdData));
	printf("Read back data: %08X\n", rdData[0]);

	printf("\n");
	addr = baseAddr + 1;
	printf("\tRead - write - read 4 Bytes at unaligned address 0x%08X\n", addr);
	tasutil_assert(clientRw.read32(addr, rdData));
	printf("Read data: %08X\n", rdData[0]);
	wrData[0] = 0x12345678;
	printf("Write 0x%08X\n", wrData[0]);
	tasutil_assert(clientRw.write32(addr, wrData[0]));
	tasutil_assert(clientRw.read32((addr & 0xFFFFFFFE), &rdData[0]));
	tasutil_assert(clientRw.read32((addr & 0xFFFFFFFE) + 4, &rdData[1]));
	printf("Read back data @0x%08X: %08X\n", (addr & 0xFFFFFFFE), rdData[0]);
	printf("Read back data @0x%08X: %08X\n", (addr & 0xFFFFFFFE) + 4, rdData[1]);

	// Reset the target
	tasutil_assert(clientRw.device_connect(TAS_CLNT_DCO_RESET_AND_HALT));

	// Example fill
	printf("\n");
	printf("Fill data starting from target address\n");
	addr = baseAddr;
	uint32_t numBytesOk;
	// fill the memory with 0x123ABCD from 0x60000000 to 0x6000007C
	tasutil_assert(clientRw.fill32(addr, 0x1234ABCD, 128));
	tasutil_assert(clientRw.read(addr, rdData, 128, &numBytesOk));
	for(uint32_t i = 0; i < (128 / 4); i++)
	{
		printf("Data @0x%08X: %08X\n", addr | (i*4), rdData[i]);
	}

	// Reset the target
	tasutil_assert(clientRw.device_connect(TAS_CLNT_DCO_RESET_AND_HALT));

	// Example with transaction list
	printf("\n");
	printf("Read - write - read with transaction list\n");
	memset(rdData, 0, BUF_SIZE);
	uint16_t accMode = 0;
	uint8_t  addrMap = 0;

	addr = 0x60000000;
	wrData[0] = 0xFFABCDEF;
	const uint8_t numTrans = 3;
	// build a list of transactions
	tas_rw_trans_st trans[numTrans] = {
			{addr, 4, accMode, addrMap, TAS_RW_TT_RD, &rdData[0] },
			{addr, 4, accMode, addrMap, TAS_RW_TT_WR, &wrData[0] },
			{addr, 4, accMode, addrMap, TAS_RW_TT_RD, &rdData[1] },
	};

	// Execute list
	tasutil_assert(clientRw.execute_trans(trans, numTrans));
	printf("Read transaction:  %08X\n", rdData[0]);
	printf("Write transaction: %08X\n", wrData[0]);
	printf("Read transaction:  %08X\n", rdData[1]);

	// Destructor of clientRw will automatically end the session
#endif

	if (args_start_reset==1)
	{
		int ret = clientRw.write32 (0xF000047C,0xC0000000); //Application Reset via OCTRL
		if (ret != TAS_ERR_NONE)
				{
					printf("Failed to reset the device, %s\n", clientRw.get_error_info());
					flasher_exit(1);
				}
	}
	flasher_exit(0);
	return 0;
}
