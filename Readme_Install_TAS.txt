1. Installation LINUX

Goto www.infineon.com/DAS
After Several Clicks you can download Version 8.0.5 Linux (x32-x64) (tar.gz) File Size 4.61MB
You will get file DAS_v8_0_5_Linux.tar.gz
Extract it -> will create folder /DAS_v8_0_5_Linux.tar with the file DAS_v8_0_5_Linux.tar
Extract further DAS_v8_0_5_Linux.tar and follow the Readme.txt 

Execute 2. TAS installation (everything)
You will be asked to accept license and default installation directories, always press y or Y if required.

-rwxrwxrwx 1 root root 4897280 May 16 14:10 DAS_v8_0_5_Linux.tar
drwxrwxrwx 1 root root       0 Sep 11 18:41 libftd2xx       <- the ftd2xxx libraries
-rwxrwxrwx 1 root root   23679 May 14 22:10 license.txt
-rwxrwxrwx 1 root root    4651 Oct 20  2023 Readme.txt      <- the readme
drwxrwxrwx 1 root root       0 Sep 14 08:34 TAS_V1_1_0      <- the installataion directory
-rwxrwxrwx 1 root root  115237 Oct 18  2023 TAS_V1_1_0-LegacyDAS.sh
-rwxrwxrwx 1 root root  101589 Oct 18  2023 TAS_V1_1_0-LegacyDAS.tar.gz
-rwxrwxrwx 1 root root 2267519 Oct 18  2023 TAS_V1_1_0-Runtime.sh
-rwxrwxrwx 1 root root 2253871 Oct 18  2023 TAS_V1_1_0-Runtime.tar.gz
-rwxrwxrwx 1 root root   68135 Oct 18  2023 TAS_V1_1_0-TasApiDemo.sh
-rwxrwxrwx 1 root root   54487 Oct 18  2023 TAS_V1_1_0-TasApiDemo.tar.gz

If you are working with VMWARE 
Manage/Virtual Machine Settings/USB Controller <- select there USB compatibility USB3.0

Open a console and run ./tas_server out of  DAS_v8_0_5_Linux.tar/TAS_V1_1_0/bin

Now Plugin the TC375 Litekit or other Kit
If you are working on a Virtual Maching you will be asked to connect it to HOST or Virtual Machine (connect it Virtual Machine - Linux).
Run ./tas_api_demo

dummy@ubuntu:~/share/HOST/AURIX_MINGW_INSTALL/DAS_v8_0_5_Linux.tar/TAS_V1_1_0/bin$ ./tas_api_demo
TAS API demo

Server Info: 
Started at 2024-09-14 08:36:52
TasServer V1.0 (Oct 18 2023)
Server IP:port: localhost:24817

Number of targets: 1
Target 0: TC37x QGBCPB (AURIX LITE KIT V2.0 (TC375) LK58AOAJ)

Connecting to the first target from the list...
TARGET:
device_type    0x10207083 (TC37x)
device_id      0x89227580 0x090A8C40 0x20241111 0x4144B9E6
device_id_hash 0xF86089A1 (QGBCPB)
dev_con_phys   DAP
identifier     AURIX LITE KIT V2.0 (TC375) LK58AOAJ
ipv4_addr      Information not accessible or not supported
max_pkt_size   rq 1048, rsp 1048
max_num_rw     32
rw_mode_mask   0x0000
addr_map_mask  0x8001
dev_con_feat   reset|HAR, unlocking

TAS channel support was not checked by this client




Basic read/write operations
	Read - write - read 1 Byte at address 0x70000000
Read data: 00
Write 0xAB
Read back data: AB

	Read - write - read 1 Byte at address 0x70000001
Read data: 00
Write 0xCD
Read back data: CD

	Read - write - read 4 Bytes at address 0x70000000
Read data: 00000000
Write 0xABCDEF09
Read back data: ABCDEF09

	Read - write - read 4 Bytes at unaligned address 0x70000001
Read data: 00ABCDEF
Write 0x12345678
Read back data @0x70000000: 34567809
Read back data @0x70000004: 00000012

Fill data starting from target address
Data @0x70000000: 1234ABCD
...
Data @0x7000007C: 1234ABCD

Read - write - read with transaction list
Read transaction:  00000000
Write transaction: FFABCDEF
Read transaction:  FFABCDEF

Goal achieved! You are able now to interact with the Board.



