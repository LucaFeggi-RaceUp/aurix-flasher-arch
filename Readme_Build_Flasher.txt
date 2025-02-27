After successfull execution of Readme_Install_TAS.txt the next steps are describing the Flasher

The tas_api_demo_main.cpp part of the Infineon package is the basis for the flasher.
creation a folder aurix_flasher_linux.
The majority of the files is a takover from Infineons package (only minor modifications to have no warnings, mainly in printf %llx replace by %lx.
What I copied into the folder
aurix_flasher.cpp <-derived from tas_api_demo_main.cpp
flash_tool_ihex.cpp <-here the Aurix Flasher functionality is implemented (approx. 2500 lines of code)
test_256k.hex <- a dummy hex file with 256kbyte
test.hex <- a dummy hex file with 6Mbyte (covering a bigger portion Program Flash)
flash_TC3xx.hex <- the code to run on target 
flash_TC4xx.hex <- the code to run on target
TC2xx is not supported yet

There is no other build dependency (Infineon Libs, etc.)

/win to build for windows
/linux to build for linux

If you were able build and you have a running tas_server in linux manually (Readme_Install_TAS.txt).

Bare metal tests are done in test_linux and test_win

Done!

The files TC3xx.hex and TC4xx.hex are build in gdb_flash_drivers.







