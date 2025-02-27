
#ifdef GNU
#include <machine/intrinsics.h>
#endif

#define flashaddress  parameter[0]
#define databuswidth  parameter[1]
#define address       parameter[2]
#define number		  parameter[3]
#define status		  parameter[4]
#define databegin	  parameter[5]
#define dummy1		  parameter[6]
#define dummy2		  parameter[7]
#define HCI_STATUS	 0xF8040004u /* HCI Status */
#define HCI_CLRERR   0xF8040014u /* HCI Clear Error*/
#define HCI_ERR      0xF8040010u /* HCI Error*/
#define DMU_GP_HOST_DFECCS 0xF804010Cu
#define DMU_GP_HOST_DFECCC 0xF8040110u
// this macro is used to address SFRs directly in C programs
#ifndef MEM
# define MEM(address) (*((volatile unsigned int *)(address)))  // makes live easier
#endif
#ifndef MEM16
# define MEM16(address) (*((volatile unsigned short *)(address)))
#endif
#ifndef MEM8
# define MEM8(address) (*((volatile unsigned char *)(address)))
#endif

#define PFRWBxy_UR_FLASHCON2_OFFS 0x0u
#define PFRWBxy_UR_FLASHCON3_OFFS 0x4u
#define PFRWBxy_UR_ECCR_OFFS 0x2000u
#define PFRWBxy_UR_ECCS_OFFS 0x2004u

void
start (void)
{
  __asm (".global _start");
  __asm (" _start:	 nop");
  __asm (" nop");
  __asm (" movh.a   %a10,hi:(0x70004000)");
  __asm (" lea      %a10,[%a10]lo:(0x70004000)");
  __asm (" ja flashing");
}

int
flashing (unsigned long *parameter, char **notused)
{
  volatile int timeout;
  volatile unsigned int i, j, len;
  volatile unsigned int addr_aligned;
  volatile unsigned int *data, read;
  volatile unsigned int low32bit, high32bit;
  volatile unsigned int burst;
  volatile unsigned int burst_buffer[0x80];
  /* FLASH PROGRAMMING */
  /* requested operaeration 1= prog  2= erase 3=ucb bmhd 4=verify*/
  MEM(HCI_CLRERR) = 0xff;
  if (MEM(&status) == 1)
    {
      MEM(&status) = 0x100;
      addr_aligned = (unsigned int) address; /* address in flash for current data 		*/
      data = (unsigned int*) databegin; /* pointer to current data in data buffer 	*/
      burst = 0x0;
      if ((flashaddress& 0x88000000)==0x80000000) burst=0x80;
      if ((flashaddress& 0x88000000)==0x88000000) burst=0x8;
      if (burst == 0x0)
	{
	  MEM(&status) = 0x100;
	  __asm ("	debug");
	}
      while (number> 0)
	{
	  for (i=0; i<burst; i++)
	    {
	      burst_buffer[i]=*data;
	      data++;
	      number-=4;
	    }
	  if (burst==0x80)
	    { MEM(0xF8085554) = 0x50;}
	  if (burst==0x8)
	    { MEM(0xF8085554) = 0x5D;}
	  i=0;
	  while (i<burst)
	    {
	      low32bit=burst_buffer[i];
	      i+=1;
	      high32bit=burst_buffer[i];
	      i+=1;
	      MEM(0xF80855F4)=low32bit;
	      __asm ("	dsync");
	      MEM(0xF80855F4)=high32bit;
	      __asm ("	dsync");
	    }

	  MEM(0xF808AA50) = addr_aligned;
	  __asm ("	dsync");
	  MEM(0xF808AA58) = 0x0;
	  __asm ("	dsync");
	  MEM(0xF808AAA8) = 0xa0;
	  __asm ("	dsync");
	  MEM(0xF808AAA8) = 0xa6;
	  __asm ("	dsync");

	  for (timeout=0x4000; timeout>0; timeout--)
	    {
	      read = MEM(HCI_STATUS);
	      __asm ("	dsync");
	      if ((read & 0x007FFFF) ==0)
		{ timeout=0; MEM(0xF8085554) = 0xFA;}
	      if (timeout==1)
		{
		  address = addr_aligned; MEM(&status) = 0x0100; MEM(0xF8085554) = 0xFA; __asm ("	debug");
		}
	    }
	  addr_aligned+=burst*4;
	}
      if ((MEM(HCI_ERR) & 0x0010FF) != 0)
	MEM(&status) = 0x0100;
      else
	MEM(&status) = 0x0;
      MEM(0xF8085554) = 0xFA;
      __asm ("	debug");
    }

  /* sector erase singular */
  /* can be optimized if host knows the amount of sectors */
  if (MEM(&status) == 2)
    {
      MEM(&status) = 0x100;
      MEM(0xF808AA50) = address;
      __asm ("	dsync");
      MEM(0xF808AA58) = number;
      __asm ("	dsync");
      MEM(0xF808AAA8) = 0x80;
      __asm ("	dsync");
      MEM(0xF808AAA8) = 0x50;
      __asm ("	dsync");
      while (1 == 1)
	{
	  for (i = 0; i < 0x4000; i++)
	    {
	      i += 1;
	      i -= 1;
	    }
	  read = MEM(HCI_STATUS);
	  __asm ("	dsync");
	  if ((read & 0x007FFFF) == 0)
	    {
	      if ((MEM(HCI_ERR) & 0x0010FF) != 0)
		MEM(&status) = 0x0100;
	      else
		MEM(&status) = 0x0;
	      __asm ("	debug");

	    }
	}
      MEM(&status) = 0x0;
      __asm ("	debug");
    }

  /* Erase and program a BMH UCB */
  if (MEM(&status) == 3)
    {

      //simple test if what is inside the UCB is identical with what has to be written;
#if 0
	  MEM(&status)=0x100;
	  len=0x800>>2;
	  burst=0x8;
	  data  = (unsigned int *) (databegin);
	  j=0;
	  while (j<len)
	  {
		  i=0;
		  while (i<burst)
		  {
			  if (MEM(address+(j+i)*4)!=data[j+i])
					  {
				  MEM(&status)=0x100;
				  __asm ("	debug");
					  }
			  i+=1;
			  if (MEM(address+(j+i)*4)!=data[j+i])
					  {
				  MEM(&status)=0x100;
				  __asm ("	debug");
					  }
			  i+=1;
		  }
		  j+=burst;
	  }
	  MEM(&status)=0x100;
	  __asm ("	debug");
#endif
#if 1
      //erase the ucb
      MEM(&status) = 0x100;
      MEM(0xF808AA50) = address;
      __asm ("	dsync");
      MEM(0xF808AA58) = 1;
      __asm ("	dsync");
      MEM(0xF808AAA8) = 0x80;
      __asm ("	dsync");
      MEM(0xF808AAA8) = 0x50;
      __asm ("	dsync");
      while (1 == 1)
	{
	  for (i = 0; i < 0x40000; i++)
	    {
	      i += 1;
	      i -= 1;
	    }
	  read = MEM(HCI_STATUS);
	  __asm ("	dsync");
	  if ((read & 0x007FFFF) == 0)
	    {
	      if ((MEM(HCI_ERR) & 0x0010FF) != 0)
		{
		  MEM(&status) = 0x0101;
		  __asm ("	debug");
		}
	      else
		{
		  MEM(&status) = 0x0;
		  goto program_copy;
		}

	    }
	}
program_copy: len = 0x800 >> 2;
      burst = 0x8;
      data = (unsigned int*) (databegin);
      j = 0;
      while (j < len)
	{
	  i = 0;
	  MEM(0xF8085554) = 0x5D;
	  while (i < burst)
	    {
	      low32bit = data[j + i];
	      MEM(0xF80855F4) = low32bit;
	      __asm ("	dsync");
	      i += 1;
	      high32bit = data[j + i];
	      MEM(0xF80855F4) = high32bit;
	      __asm ("	dsync");
	      i += 1;
	    }
	  MEM(0xF808AA50) = address+ (j<<2);
	  __asm ("	dsync");
	  MEM(0xF808AA58) = 0x0;
	  __asm ("	dsync");
	  MEM(0xF808AAA8) = 0xa0;

	  MEM(0xF808AAA8) = 0xa6;
	  __asm ("	dsync");
	  for (timeout = 0x4000; timeout > 0; timeout--)
	    {
	      read = MEM(HCI_STATUS);
	      __asm ("	dsync");
	      if ((read & 0x007FFFF) == 0)
		{
		  timeout = 0;
		  MEM(0xF8085554) = 0xFA;
		}
	      if (timeout == 1)
		{
		  address= addr_aligned;
		  MEM(&status) = 0x0102;
		  MEM(0xF8085554) = 0xFA;
		  __asm ("	debug");
		}
	    }
	  j += burst;
	  if ((MEM(HCI_ERR) & 0x0010FF) != 0)
	    {
	      MEM(&status) = 0x0103;
	      __asm ("	debug");
	    }
	}
      MEM(&status) = 0x0;
      __asm ("	debug");
#endif
    }
  //Calculating a checksum over a flashrange to check if the content is equal
  //main purpose is here to reduce the amount of erase and pogramming steps, if the content is already in flash
  if (MEM(&status) == 4)
    {
      status=0x100;
      data = (unsigned int *) (databegin);
      while (data[0]!=0xFFFFFFFF)
	{
	  unsigned int *addr_begin;
	  unsigned int len_verify;
	  volatile unsigned int checksum;
	  volatile unsigned int tmp1,tmp2;
	  unsigned int ii=0;
	  checksum=0;
	  addr_begin=(unsigned int *) data[0];
	  len_verify=data[1];
	  if (data[5]!=0) //PFLASH
	    {
	      MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS)=MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS) | 0x55000000;
	      __asm ("	dsync");
	      MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS)=MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS) | 0x400;
	      __asm ("	dsync");
	    }
	  else //DFLASH and UCBS
	    {
	      //by default in HF_ECCC TRAPDIS and ECCCORDIS are disabled
	      MEM(DMU_GP_HOST_DFECCC)=0xC0000003;
	      __asm ("	dsync");
	    }
	  if (data[6]==*addr_begin)
	    {
	      while (ii<len_verify)
		{
		  checksum+=*addr_begin;
		  addr_begin++;
		  ii+=4;
		}
	      if (checksum==data[2]) data[3]=0xAAAAAAAA;
	      else data[3]=0xEEEEEEEE;
	    }
	  else
	    {
	      data[3]=0xEEEEEEEE;
	    }
	  if (data[5]!=0) //PFLASH
	    {
	      tmp1=MEM(data[5]+PFRWBxy_UR_ECCS_OFFS);
	      if ((tmp1 & ~0x80008)!=0) data[3]=0xEEEEEEEE;
	      MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS)=MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS) | 0x55000000;
	      __asm ("	dsync");
	      MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS)=MEM(data[5]+PFRWBxy_UR_FLASHCON2_OFFS) | ~0x400;
	      __asm ("	dsync");
	      tmp2=MEM(data[5]+PFRWBxy_UR_ECCS_OFFS);
	      data[6]=tmp1;
	      data[7]=tmp2;
	    }
	  else //DFLASH and UCBS
	    {
	      tmp1=MEM(DMU_GP_HOST_DFECCS);
	      if ((tmp1 & ~0x80008)!=0) data[3]=0xEEEEEEEE;
	      MEM(DMU_GP_HOST_DFECCC)=0xC0000003;
	      __asm ("	dsync");
	      MEM(DMU_GP_HOST_DFECCC)=0xC0000000;
	      __asm ("	dsync");
	      tmp2=MEM(DMU_GP_HOST_DFECCS);
	      data[6]=tmp1;
	      data[7]=tmp2;
	    }
	  data+=8;
	}
      MEM(&status)=0x0;
      __asm ("	debug");
    }

  MEM(&status) = 0x100;
  __asm ("	debug");
  return 0;
}


