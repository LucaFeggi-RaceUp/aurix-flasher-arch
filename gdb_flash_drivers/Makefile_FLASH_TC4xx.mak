# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += 
CPP_SRCS = flash_TC4xx.c 

OBJS +=flash_TC4xx.o 

BININSTALLROOT=/e/AURIX_MINGW_INSTALL/tricore_1131_mingw/bin/
CC=$(BININSTALLROOT)tricore-elf-gcc.exe
CPP=$(BININSTALLROOT)tricore-elf-gcc.exe
AS=$(BININSTALLROOT)tricore-elf-as.exe
LD=$(BININSTALLROOT)tricore-elf-ld.exe
AR=$(BININSTALLROOT)tricore-elf-ar.exe
OBJDUMP=$(BININSTALLROOT)tricore-elf-objdump.exe
OBJCOPY=$(BININSTALLROOT)tricore-elf-objcopy.exe

CC_INCLUDES =  
#TC1.6
CC_FLAGS = -Wall -g3 -O2 -fno-peephole2 -fno-common -fno-short-enums -mtc162 -fsingle-precision-constant \
           $(CC_INCLUDES) -save-temps -nostartfiles -nodefaultlibs -nostdlib -c
AS_FLAGS = -mtc162
LINKER_FLAGS= --mcpu=tc161 -T flash_TC4xx.ld 
LIBS= 

LIBRARY_PATH= 

EXECUTEABLE= flash_TC4xx.elf
SREC= flash_TC4xx.sre
IHEX= flash_TC4xx.hex
DISASM= DisAsm_flash_TC4xx.Lst


$(EXECUTEABLE): $(OBJS) flash_TC4XX.ld 
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LD) $(LINKER_FLAGS) -o $(EXECUTEABLE) $(LIBRARY_PATH) $(LIBS) $(OBJS) $(ADDOBJS) $(LIBS) 
	$(OBJDUMP) -d $(EXECUTEABLE) >$(DISASM)
	$(OBJCOPY) $(EXECUTEABLE) -O srec $(SREC)
	$(OBJCOPY) $(EXECUTEABLE) -O ihex $(IHEX)
	cp $(IHEX) ../win/$(IHEX)
	@echo 'Finished building target: $@'
	@echo ' '



flash_TC4xx.o: flash_TC4xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(CC) -S $(CC_FLAGS) -c $<  
	$(AS) $(AS_FLAGS) flash_TC4xx.s  -o flash_TC4xx.o
	@echo 'Finished building: $<'
	@echo ' '



clean:
	-rm -f flash_TC4xx.elf
	-rm -f flash_TC4xx.o
	-rm -f flash_TC4xx.i
	-rm -f flash_TC4xx.sre
	-rm -f flash_TC4xx.hex
	
