




$ ./AurixFlasher --help
AURIX Flasher Software Tool 1.0.8.0, built on 7/7/2023 4:18:22 PM
Usage: AURIXFlasher.exe <COMMAND> [<COMMAND>] [...]
<COMMAND>            List of available commands:
  -l                 List of devices supported (-list)
  -hex <file>        Specify flash memory content in INTEL HEX format
  -elf <file>        Specify flash memory content in elf-file format
  -erase <arg>       Specify flash memory erasing options (-e)
         <arg>       if 'on': Erase used flash memory only (default)
         <arg>       if 'all': Erase all flash memory
         <arg>       if 'off': Disable erase operation
  -ver <arg>         Specify flash memory post verification options (-v)
       <arg>         if 'on': Enable Flash memory verify operation
       <arg>         if 'off: Disable Flash memory verify operation (default)
  -ucb  <arg>         Specifiy UCB options for TC3xx devices (-bmhd)
        <arg>        if 'on': Enable programmig of BMHD into UCB memory (WARNING: wrong BMHD may brick your device!)
        <arg>        if 'off': Disable programming of BMHD into UCB memory (default)
  -connect <arg>     Specify the connection type to the device
           <arg>     if '0': Connect device with a 'hot attach' (WARNING: the device must be halted prior the flashing o
peration!)
           <arg>     if '6': Connect device by performing a reset&halt (default)
  -start <arg>       Specify task at the end of the process
         <arg>       if 'on': Start the device by performing a reset (default)
         <arg>       if 'off': Leave the device in halt state
  -log <file.xml>    Save a log file into <file.xml> in XML format that contains more detailed information about errors
and warnings.

The aim is to replace the Infineon AURIX Flasher Tool 1.0.8.0 or successors with linux and windows versions.
- Ensure compatibility for one by one replacement in Aurix Developer Studio.
- Ensure full code visibility to enable others modifications.
Added features to be faster ...
Important is the new feature erase/program only if needed.

$ ../linux/aurix_flasher 
Volumit AURIX Flasher Software Tool 0.0.0.1, built on Feb 22 2025 09:59:28
Usage: AURIXFlasher.exe <COMMAND> [<COMMAND>] [...]
<COMMAND>            List of available commands:
  -l                 List of devices supported (-list)
  -hex   <file>      Specify flash memory content in INTEL HEX format, use "file" if spaces are in
  -elf   <file>      Specify flash memory content in elf-file format, use "file" if spaces are in
  -freq  <number>    Specify the frequency Hz for DAP/JTAG as decimal
         <number>    between 1000000...20000000 (1MHz...20MHz)
         <number>    (default) 150000000 (15MHz)
  -erase <arg>       Specify flash memory erasing options
         <arg>       if 'on': Erase used flash memory only (default)
         <arg>       if 'all': Erase all flash memory - overrules -opt on
         <arg>       if 'off': Disable erase operation
  -start <arg>       Specify task at the end of the process
         <arg>       if 'on': Start the device by performing a reset (default)
         <arg>       if 'off': Leave the device in halt state
  -opt   <arg>       Optimizes the flashing procedure
         <arg>       if 'on': Do not erase & program areas with identical values (default)
         <arg>       if 'off': Turn off the optimization
  -page  <number>    Specify page byte filling for undefined values
         <number>    between 00..FF as hex value
         <number>    (default) 00 
  -mem   <arg>       List memory usage of the device
         <arg>       if 'on': list
         <arg>       if 'off': do not list (default)
  -map   <arg>       Abort if loaded data is not fitting to memory map of the device
         <arg>       if 'on': abort (default)
         <arg>       if 'off': do not abort
  -ucb   <arg>       Specify UCB options
         <arg>       if 'on': Enable programmig of BMHD into UCB memory (WARNING: wrong BMHD may brick your device!)
         <arg>       if 'off': Disable programming of BMHD into UCB memory (default)
  -gui   <arg>       GUI Usage
         <arg>       if 'on': not supported
         <arg>       if 'off': Supported (default)
  -id    <number>    Board id which TAS has to use
         <arg>       'list' list the board id which connected to TAS
  -ver   <arg>       Specify flash memory post verification options
         <arg>       if 'on': Enable Flash memory verify operation
         <arg>       if 'off: Disable Flash memory verify operation (default)
  -log   <arg>       Generates Logging Information (huge amount of log) on stdout
         <arg>       if 'on': Enable Logging
         <arg>       if 'off: Disable Logging (default)

Licensing:
Infineons part of TAS is Apache 2.0
My addons are MIT License





