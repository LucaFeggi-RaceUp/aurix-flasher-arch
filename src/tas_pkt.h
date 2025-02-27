/*
 * ********************************************************************************************************************
 *  Copyright 2022-2023 Infineon Technologies AG
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *      http://www.apache.org/licenses/LICENSE-2.0
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * ******************************************************************************************************************** */
#ifndef __tas_pkt_h
#define __tas_pkt_h


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	TAS_PKT_PROTOC_VER_1 = 1,  // Initial protocol version (value 0 is unknown/undefined/unused etc.)
} tas_protoc_ver_et;
// Used in tas_server_info_st.supp_protoc_ver -> limited to 31 versions

enum {
	TAS_PORT_NUM_SERVER_DEFAULT = 24817,  // Local network TasServer
	TAS_PORT_NUM_PROXY_DEFAULT  = 24818,  // Remote test farm proxy server
	TAS_PORT_NUM_DEVICE_DEFAULT = 24823,  // TasDeviceServer locally connected to TasServer
};  // Unused (220226) in https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers

enum {
	TAS_NAME_LEN64 = 64,
	TAS_NAME_LEN32 = 32,
	TAS_NAME_LEN16 = 16,
	TAS_NAME_LEN8  =  8,

	TAS_HOST_ADDR_LEN = 128,

	TAS_MAX_PKT_SIZE_1KB = 1024,  // Limit the maximum size of certain packet types
};

enum {
	TAS_UNLOCK_MAX_KEY_LEN       = 512,  // Bytes
	TAS_UNLOCK_MAX_CHALLENGE_LEN = 512,  // Bytes
};

typedef enum { 
	TAS_CLIENT_TYPE_UNKNOWN = 0,
	TAS_CLIENT_TYPE_RW      = 1,
	TAS_CLIENT_TYPE_CHL     = 2,
	TAS_CLIENT_TYPE_TRC     = 3,
} tas_client_type_et;

enum {
	TAS_PL2_MAX_PKT_SIZE     = 0x10008,  // Max. 64KB payload
	TAS_PL2_MAX_PKT_SIZE_MIN = 128,      // Minimum size an agent must support
	TAS_PL0_DATA_BLK_SIZE    = 1024,     // Limited by protocol constraints
	TAS_PL1_CHL_MAX_MSG_SIZE = 1024,     // Limited by protocol constraints
};

typedef uint8_t tas_pl_err_et8;
typedef enum {
	TAS_PL_ERR_NO_ERROR       = 0x08,
	TAS_PL_ERR_PARAM          = 0x10,  // Wrong parameter value
	TAS_PL_ERR_NOT_SUPPORTED  = 0x12,  // Command or parameter not supported by this implementation or setup
	TAS_PL_ERR_USAGE          = 0x14,  // Not correctly used (e.g. wrong sequence of commands)
	TAS_PL_ERR_PROTOCOL       = 0x1E,  // Packet layer protocol error

	TAS_PL1_ERR_CMD_FAILED    = 0x20,

	TAS_PL1_ERR_SERVER_LOCKED = 0x32,

	TAS_PL1_ERR_SESSION       = 0x38,  // Session name or password mismatch

	TAS_PL1_ERR_DEV_RESET     = 0x44,  // Device reset was detected. Sent to all clients as an unsolicited PL2 packet
	TAS_PL1_ERR_DEV_LOCKED    = 0x46,  // Device is locked (no access possible)
	TAS_PL1_ERR_DEV_ACCESS    = 0x48,  // Device access (e.g. DAP connection)

	                                                    // Access
	TAS_PL0_ERR_NO_ERROR      = 0x80,                   // yes
	TAS_PL0_ERR_DEV_LOCKED    = TAS_PL1_ERR_DEV_LOCKED, // no     Device is locked (no access possible)
	TAS_PL0_ERR_DEV_ACCESS    = TAS_PL1_ERR_DEV_ACCESS, // no     Device access (e.g. DAP connection)
	TAS_PL0_ERR_ACC_MODE      = 0x89,                   // no     Set acc_mode is not supported
	TAS_PL0_ERR_ADDR_MAP      = 0x8A,                   // no     Set addr_map is not supported
	TAS_PL0_ERR_ADDR_BLOCKED  = 0x8B,                   // no     TasAgent protection prevents access to this address
	TAS_PL0_ERR_DATA          = 0x8D,                   // tried  RW access was not (completely - blk) successful (e.g. device internal bus error)
	TAS_PL0_ERR_CONSEQUENTIAL = 0x98,                   // impl   Consequential error since a previous PL0 command failed. Whether the access took place is implementation specific. Recommendation is no.

	TAS_PL0_ERR_HIGHEST       = 0x9F,                   // no     Delimiter for PL0 error codes

} tas_pl_err_et;


typedef enum {

    // PL0 RW commands
	TAS_PL0_CMD_ACCESS_MODE     = 0x10,  // No response pkt
	TAS_PL0_CMD_ADDR_MAP        = 0x11,  // No response pkt
	TAS_PL0_CMD_BASE_ADDR32     = 0x15,  // No response pkt
	TAS_PL0_CMD_BASE_ADDR64     = 0x16,  // No response pkt
	TAS_PL0_CMD_WR8             = 0x20,  // TAS_PL0_ERR_
	TAS_PL0_CMD_RD8             = 0x21,  // TAS_PL0_ERR_
	TAS_PL0_CMD_WR16            = 0x22,  // TAS_PL0_ERR_
	TAS_PL0_CMD_RD16            = 0x23,  // TAS_PL0_ERR_
	TAS_PL0_CMD_WR32            = 0x24,  // TAS_PL0_ERR_
	TAS_PL0_CMD_RD32            = 0x25,  // TAS_PL0_ERR_
	TAS_PL0_CMD_WR64            = 0x26,  // TAS_PL0_ERR_
	TAS_PL0_CMD_RD64            = 0x27,  // TAS_PL0_ERR_
	TAS_PL0_CMD_WRBLK           = 0x2A,  // TAS_PL0_ERR_
	TAS_PL0_CMD_FILL            = 0x2B,  // TAS_PL0_ERR_
	TAS_PL0_CMD_RDBLK           = 0x2C,  // TAS_PL0_ERR_
	TAS_PL0_CMD_RDBLK1KB        = 0x2D,  // TAS_PL0_ERR_NO_ERROR (used for response if 1kb data read without error)

	// PL1 commands
	TAS_PL1_CMD_SERVER_CONNECT  = 0x80,

	TAS_PL1_CMD_GET_TARGETS     = 0x86,
	TAS_PL1_CMD_GET_CLIENTS     = 0x87,

	TAS_PL1_CMD_SESSION_START   = 0xA1,
	TAS_PL1_CMD_PING            = 0xA2,
	TAS_PL1_CMD_DEVICE_CONNECT  = 0xA8,
	TAS_PL1_CMD_DEVICE_RESET_COUNT = 0xAA,

	TAS_PL1_CMD_GET_CHALLENGE   = 0xAC,
	TAS_PL1_CMD_SET_DEVICE_KEY  = 0xAD,

	TAS_PL1_CMD_PL0_START       = 0xB0,
	TAS_PL1_CMD_PL0_END         = 0xB1,

	TAS_PL1_CMD_CHL_SUBSCRIBE   = 0xC0,
	TAS_PL1_CMD_CHL_UNSUBSCRIBE = 0xC2,
	TAS_PL1_CMD_CHL_MSG_C2D     = 0xCC,
	TAS_PL1_CMD_CHL_MSG_D2C     = 0xCD,

	TAS_PL1_CMD_TRC_SUBSCRIBE   = 0xD0,
	TAS_PL1_CMD_TRC_UNSUBSCRIBE = 0xD2,
	TAS_PL1_CMD_TRC_DATA        = 0xD4,

	TAS_PL1_CMD_ERROR           = 0xEE,
} tas_pl_cmd_et;

typedef enum {  // Can be bitwise ored
	TAS_DEV_CON_FEAT_NONE           =      0,
	TAS_DEV_CON_FEAT_RESET          = 0x0001,
	TAS_DEV_CON_FEAT_RESET_AND_HALT = 0x0003,
	TAS_DEV_CON_FEAT_UNLOCK         = 0x0010,
	TAS_DEV_CON_FEAT_UNLOCK_CNR     = 0x0030,  // Unlocking with challenge and response protocol
	TAS_DEV_CON_FEAT_UNKNOWN        = 0x4000,
	TAS_DEV_CON_FEAT_UNKNOWN_RESET  = 0x4001,
} tas_dev_con_feat_et;

typedef enum {
	// Connections where the identifier is provided by a unique tool access HW identifier
	TAS_DEV_CON_PHYS_UNKNOWN    = 0,
	TAS_DEV_CON_PHYS_JTAG       = 0x01,
	TAS_DEV_CON_PHYS_DAP        = 0x10,  // DAP, DXCPL or DXCM
	TAS_DEV_CON_PHYS_DAP_DAP    = 0x11,
	TAS_DEV_CON_PHYS_DAP_SPD    = 0x12,
	TAS_DEV_CON_PHYS_DAP_DXCPL  = 0x13,
	TAS_DEV_CON_PHYS_DAP_DXCM   = 0x14,
	TAS_DEV_CON_PHYS_SWD        = 0x20,
	TAS_DEV_CON_PHYS_ACC_HW_MAX = 0x7F,

	// Connections which have an intrinsic unique identifier
	TAS_DEV_CON_PHYS_ETH        = 0x80,
}  tas_dev_con_phys_et;

typedef enum {
	TAS_DEV_ULCRO_UDID     = 0x01,  // Challenge is the unique device ID which can be read from the locked device
	TAS_DEV_ULCRO_UDID_RST = 0x81,  // Unique device ID can only be read after a reset
	TAS_DEV_ULCRO_CR       = 0x04,  // Challenge is read from the locked device
	TAS_DEV_ULCRO_CR_RST   = 0x84,  // Challenge can only be read after a reset
	TAS_DEV_ULCRO_CUSTOM0  = 0xC0,  // Option 0 for custom protocol for retrieving the challenge
	TAS_DEV_ULCRO_CUSTOM1  = 0xC1,  // Option 1
	TAS_DEV_ULCRO_CUSTOM2  = 0xC2,  // Option 2
	TAS_DEV_ULCRO_CUSTOM3  = 0xC3,  // Option 3
} tas_dev_unlock_cr_option_et;
// Option for getting the challenge for unlocking

typedef enum {
	TAS_DEV_ULO_HOT_ATTACH         = 0x01,  // Unlocking is possible any time
	TAS_DEV_ULO_AFTER_RST_BY_FW    = 0x08,  // Unlocking by FW before application SW is started
	TAS_DEV_ULO_AFTER_RST_BY_APPSW = 0x09,  // Unlocking by application SW in a time window after reset
} tas_dev_unlock_option_et;


typedef enum {
	TAS_PL0_ACC_MODE_DEFAULT = 0x0000,  // Default RW access mode for the target device
} tas_pl0_acc_mode_et;
// Target specific access mode



/*
All values are little endian
Three levels of packet wrapping:
PL0 RW access steps, wrapped by PL1
PL1 RW, CHL, trace CHL
PL1 guarantees atomicity for the sequence of RW transactions
PL2 Just an initial 32 bit number which gives the overall PL1 length in bytes + 4
*/

// Packet level 2
typedef struct {
	union {
		struct { 
			uint16_t length;
			uint8_t  type;
			uint8_t  param;
		};
		uint32_t u32;
	};
} tas_pl2_header_st;

// Packet level 1 which is wrapping packet level 0

typedef struct {
	uint8_t  wl;         // Word Length of packet excluding this first word
	uint8_t  cmd;        // TAS_PL1_CMD_xxx
	uint8_t  con_id;     // Connection identifier of TasDispatcher
} tas_pl1rq_header_st;

typedef struct {
	uint8_t  wl;         // Word Length of packet excluding this first word
	uint8_t  cmd;        // TAS_PL1_CMD_xxx
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // tas_pl_err_et
} tas_pl1rsp_header_st;



typedef struct {
	char      server_name[TAS_NAME_LEN64];
	uint16_t  v_minor;          // Version minor
	uint16_t  v_major;          // Version major
	uint32_t  supp_protoc_ver;  // Supported protocol versions.  tas_protoc_ver_et defines the bit number
	uint32_t  supp_chl_target;  // Supported channel targets.    tas_chl_target_et defines the bit number
	uint32_t  supp_trc_type;    // Supported trace stream types. tas_trc_type_et   defines the bit number
	uint32_t  reserved[4];
	char      date[16];         // String from __DATE__ macro at compile time
	uint64_t  start_time_us;    // Time the server was started, as microseconds elapsed since midnight, January 1, 1970
} tas_server_info_st;

typedef struct {
	uint8_t  wl;          // 10
	uint8_t  cmd;         // TAS_PL1_CMD_SERVER_CONNECT
	uint16_t reserved;    // 0

	char     client_name[TAS_NAME_LEN32];
	char     user_name[TAS_NAME_LEN16];
	uint32_t client_pid;  // Process ID of client

} tas_pl1rq_server_connect_st;

typedef struct {
	uint8_t  wl;         // 25
	uint8_t  cmd;        // TAS_PL1_CMD_SERVER_CONNECT
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_CMD_FAILED or TAS_PL1_ERR_SERVER_LOCKED
	uint32_t reserved1;  // Ensures no padding by compiler for 64 bit alignment

	tas_server_info_st server_info;

	uint64_t challenge;

} tas_pl1rsp_server_connect_st;

typedef struct {
	uint8_t  wl;         // ?
	uint8_t  cmd;        // TAS_PL1_CMD_SERVER_UNLOCK
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_CMD_FAILED or TAS_PL1_ERR_SERVER_LOCKED

	// Add missing stuff here

} tas_pl1rsp_server_unlock_st;


typedef struct {
	char     identifier[TAS_NAME_LEN64];  // Unique access HW name or IP address of device
	uint32_t device_type;    // Device type identifier (IEEE 1149.1 device ID). 0 if no device connected
	uint32_t device_id[4];   // 128 bit unique device ID
	uint8_t  dev_con_phys;   // tas_dev_con_phys_et
	uint8_t  num_client;     // Number of attached clients
	uint16_t reserved;
} tas_target_info_st;  // 76 bytes

typedef struct {
	uint8_t  wl;          // 0
	uint8_t  cmd;         // TAS_PL1_CMD_GET_TARGETS
	uint8_t  start_index; // If 0 the list of all targets is sampled by the TasServer
	uint8_t  reserved;    // 0
} tas_pl1rq_get_targets_st;

typedef struct {
	uint8_t  wl;         // 1...255 -> TAS_MAX_PKT_SIZE_1KB
	uint8_t  cmd;        // TAS_PL1_CMD_GET_TARGETS
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR or TAS_PL1_ERR_SERVER_LOCKED

	uint8_t  num_target;
	uint8_t  start_index;
	uint8_t  num_now;
	uint8_t  reserved1;  // 0

	// Followed by tas_target_info_st[num_now] 

} tas_pl1rsp_get_targets_st;


typedef struct {
	char     client_name[TAS_NAME_LEN32];
	char     user_name[TAS_NAME_LEN16];
	uint32_t client_pid;           // Process ID of client
	uint8_t  client_type;          // tas_client_type_et
	uint8_t  reserved[3];          // 0
	uint64_t client_connect_time;  // Time in us since tas_server_info_st.start_time
	uint64_t num_byte_c2s;
	uint64_t num_byte_s2c;
} tas_target_client_info_st;

typedef struct {
	uint8_t  wl;          // 16
	uint8_t  cmd;         // TAS_PL1_CMD_GET_CLIENTS
	uint8_t  start_index; // If 0 the list of all clients is sampled by the TasServer
	uint8_t  reserved;    // 0

	char     identifier[TAS_NAME_LEN64];  // Target identifier. TAS_PL_ERR_PARAM if not valid
} tas_pl1rq_get_clients_st;

typedef struct {
	uint8_t  wl;         // 7...255 -> TAS_MAX_PKT_SIZE_1KB
	uint8_t  cmd;        // TAS_PL1_CMD_GET_CLIENTS
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL_ERR_PARAM or TAS_PL1_ERR_SERVER_LOCKED

	uint8_t  num_client;
	uint8_t  start_index;
	uint8_t  num_now;
	uint8_t  reserved1;  // 0

	char     session_name[TAS_NAME_LEN16];  // Session name and time only if start_index is 0
	uint64_t session_start_time_us;  // Time in microseconds since tas_server_info_st.start_time_us

	// Followed by tas_target_client_info_st[num_now] 

} tas_pl1rsp_get_clients_st;


typedef struct {
	uint8_t  wl;           // 51
	uint8_t  cmd;          // TAS_PL1_CMD_SESSION_START
	uint8_t  con_id;       // Connection identifier of TasDispatcher
	uint8_t  client_type;  // tas_client_type_et
	uint8_t  param8[4];    // E.g. [0] for chl_target
	uint64_t param64;      // E.g. for chl_param
	char   identifier[TAS_NAME_LEN64];   // Unique access HW name or IP address of device
	char   session_name[TAS_NAME_LEN16];
	char   session_pw[TAS_NAME_LEN16];   // Password
} tas_pl1rq_session_start_st;


typedef struct {

	uint32_t max_pl2rq_pkt_size;
	uint32_t max_pl2rsp_pkt_size;

	uint32_t device_type;       // Device type identifier (IEEE 1149.1 device ID). 0 if no device connected
	uint32_t device_id[4];      // 128 bit unique device ID

	uint32_t ipv4_addr;         // IPV4 address of the device. 
								// Same as identifier for TAS_DEV_CON_PHYS_ETH or copied from tas_chl_osw_config_st.

	uint16_t dev_con_feat;      // tas_dev_con_feat_et 
	uint8_t  dev_con_phys;      // tas_dev_con_phys_et 
	uint8_t  pl0_max_num_rw;    // Maximum number of RW transactions in a PL1 packet

	uint16_t pl0_rw_mode_mask;  // Mask for supported RW access mode bits
	uint16_t pl0_addr_map_mask; // Mask for supported address maps. Bit 15 represents TAS_AM15.

	uint16_t msg_length_c2d;    // Maximum length of messages sent from client to device. 0 if not ClientChl or channels not supported
	uint16_t msg_length_d2c;    // Maximum length of messages sent from device to client. 0 if not ClientChl or channels not supported

	uint8_t  msg_num_c2d;       // Maximum number of messages sent from client to device
	uint8_t  msg_num_d2c;       // Maximum number of messages sent from device to client
	uint16_t reserved;

} tas_con_info_d2s_st;  // Only this part is provided by a TasAgent running on the device

typedef struct {
	uint32_t max_pl2rq_pkt_size;
	uint32_t max_pl2rsp_pkt_size;

	uint32_t device_type;       // Device type identifier (IEEE 1149.1 device ID). 0 if no device connected
	uint32_t device_id[4];      // 128 bit unique device ID

	uint32_t ipv4_addr;         // IPV4 address of the device. 
								// Same as identifier for TAS_DEV_CON_PHYS_ETH or copied from tas_chl_osw_config_st.

	uint16_t dev_con_feat;      // tas_dev_con_feat_et 
	uint8_t  dev_con_phys;      // tas_dev_con_phys_et 
	uint8_t  pl0_max_num_rw;    // Maximum number of RW transactions in a PL1 packet

	uint16_t pl0_rw_mode_mask;  // Mask for supported RW access mode bits
	uint16_t pl0_addr_map_mask; // Mask for supported address maps. Bit 15 represents TAS_AM15.

	uint16_t msg_length_c2d;    // Maximum length of messages sent from client to device. 0 if not ClientChl or channels not supported
	uint16_t msg_length_d2c;    // Maximum length of messages sent from device to client. 0 if not ClientChl or channels not supported

	uint8_t  msg_num_c2d;       // Maximum number of messages sent from client to device that will be buffered in the device
	uint8_t  msg_num_d2c;       // Maximum number of messages sent from device to client that will be buffered in the device
	uint16_t reserved;

	// Extensions to tas_con_info_d2s_st which are only transmitted between TasServer and TasClient

	char     identifier[TAS_NAME_LEN64];  // Unique access HW name or IP address of device. Empty if not connected.
	uint32_t device_id_hash;    // 32 bit hash of device_id, calculated by TasClient
	char     device_id_hash_str[TAS_NAME_LEN8];  // ASCII string generated with tasutil_hash32_to_str()

} tas_con_info_st;


typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_PING
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  reserved;   // 0
} tas_pl1rq_ping_st;

typedef struct {
	uint8_t  wl;         // 8
	uint8_t  cmd;        // TAS_PL1_CMD_SESSION_START or TAS_PL1_CMD_PING
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR (check acc_hw and device type in con_info)

	uint8_t  protoc_ver_min;  // Lowest supported protocol version
	uint8_t  protoc_ver_max;  // Highest supported protocol version
	uint8_t  num_instances;   // Number of matches for the identifier from tas_pl1rq_attach_st
	uint8_t  reserved;        // 0

	tas_con_info_d2s_st con_info_d2s;

} tas_pl1rsp_ping_d2s_st;  // Response for TAS_PL1_CMD_SESSION_START or TAS_PL1_CMD_PING for d2s

typedef struct {
	uint8_t  wl;         // 31
	uint8_t  cmd;        // TAS_PL1_CMD_SESSION_START or TAS_PL1_CMD_PING
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR (check acc_hw and device type in con_info)

	uint8_t  protoc_ver_min;  // Lowest supported protocol version
	uint8_t  protoc_ver_max;  // Highest supported protocol version
	uint8_t  num_instances;   // Number of matches for the identifier from tas_pl1rq_attach_st
	uint8_t  reserved;        // 0

	tas_con_info_st con_info;

} tas_pl1rsp_ping_st;  // Response for TAS_PL1_CMD_SESSION_START or TAS_PL1_CMD_PING for s2c
typedef tas_pl1rsp_ping_st tas_pl1rsp_session_start_st;

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_GET_CHALLENGE
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  reserved;   // 0

	uint16_t ulcro;      // tas_dev_unlock_cr_option_et
	uint16_t reserved1;  // 0

} tas_pl1rq_get_challenge_st;

typedef struct {
	uint8_t  wl;         // 1 ... (1 + N) depending on challenge_length
	uint8_t  cmd;        // TAS_PL1_CMD_GET_CHALLENGE
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_CMD_FAILED or TAS_PL1_ERR_DEV_ACCESS

	uint16_t challenge_length; // Challenge length in bytes.
	uint16_t reserved;   // 0

	// Followed by N data words for the challenge 

} tas_pl1rsp_get_challenge_st;  // Response

typedef struct {
	uint8_t  wl;         // ?
	uint8_t  cmd;        // TAS_PL1_CMD_DEVICE_UNLOCK
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_CMD_FAILED

	// Add missing stuff here

} tas_pl1rsp_device_unlock_get_challenge_st;

typedef struct {
	uint8_t  wl;         // 1 ... (1 + N) depending on key_length
	uint8_t  cmd;        // TAS_PL1_CMD_SET_DEVICE_KEY
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  reserved;   // 0

	uint16_t ulo;        // tas_dev_unlock_option_et
	uint16_t key_length; // Key length in bytes.

	// Followed by N data words for the key. The key will be used if needed 
} tas_pl1rq_set_device_key_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_SET_DEVICE_KEY
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR (key will be used by following device_connect)
} tas_pl1rsp_set_device_key_st;  // Response

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_DEVICE_CONNECT
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  reserved;   // 0

	uint16_t option;     // tas_dev_con_feat_et but only _RESET, _RESET_AND_HALT, _UNLOCK
	uint16_t reserved1;  // 0
} tas_pl1rq_device_connect_st;

typedef struct {
	uint8_t  wl;         // 2
	uint8_t  cmd;        // TAS_PL1_CMD_DEVICE_CONNECT
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_DEV_ACCESS, TAS_PL1_ERR_DEV_LOCKED or TAS_PL1_ERR_CMD_FAILED (associated feat_used bit not set)

	uint16_t feat_used;  // tas_dev_con_feat_et used (_RESET, _RESET_AND_HALT, _UNLOCK)
	uint16_t reserved;   // 0

	uint32_t device_type;  // Device type identifier (IEEE 1149.1 device ID). 0 if no device connected

} tas_pl1rsp_device_connect_st;  // Response

typedef struct {
	uint32_t porst;  // Detected power-on resets (PORST)
	uint32_t reset;  // Detected resets
} tas_reset_count_st;
// The detection possibilities depend on the access path and the device type
// The TasServer increments the value each time when a PORST or reset is detected. 
// Please note:
// - Not all device connections support this feature
// - If there is no interaction with the device, only the last PORST of a 
//   sequence of PORSTs will increment the value.
// - The initial value can be different from 0, if another TasClient has
//   already established a device connection.


typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_DEVICE_RESET_COUNT
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  reserved;   // 0
} tas_pl1rq_device_reset_count_st;

typedef struct {
	uint8_t  wl;         // 2
	uint8_t  cmd;        // TAS_PL1_CMD_DEVICE_RESET_COUNT
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, or TAS_PL1_ERR_CMD_FAILED

	tas_reset_count_st reset_count;

} tas_pl1rsp_device_reset_count_st;  // Response


typedef enum {  // Channel target
	TAS_CHL_TGT_UNKNOWN = 0,
	TAS_CHL_TGT_DMM     = 1,  // Device memory mapped protocol
} tas_chl_target_et;
// Used in tas_server_info_st.supp_chl_target -> limited to 31 different targets


typedef enum {  // Channel type
	TAS_CHT_NONE = 0,
	TAS_CHT_SEND = 0x01,  // Message is sent from client to device
	TAS_CHT_RCV  = 0x02,  // Message is received by client from device
	TAS_CHT_BIDI = 0x03,  // Only use if the client always knows when to send and when to receive 
} tas_cht_et;

typedef enum {  // channel subscribe option
	TAS_CHSO_DEFAULT = 0,
	TAS_CHSO_EXCLUSIVE = 0x01,
} tas_chso_et;

enum {
	TAS_CHL_NUM_MAX = 32,
	TAS_CHL_LOWEST_PRIORITY = 31,
};

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_CHL_SUBSCRIBE
	uint16_t reserved;   // 0

	uint8_t  chl;        // 0 <= chl < MCD_CHL_NUM_MAX
	uint8_t  cht;        // tas_cht_et
	uint8_t  chso;       // tas_chso_et
	uint8_t  prio;       // 0 <= chl <= MCD_CHL_LOWEST_PRIORITY

} tas_pl1rq_chl_subscribe_st;

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_CHL_SUBSCRIBE
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR or TAS_PL1_ERR_CMD_FAILED

	uint8_t  chl;        // 0 <= chl < MCD_CHL_NUM_MAX
	uint8_t  cht;        // tas_cht_et
	uint8_t  chso;       // tas_chso_et
	uint8_t  prio;       // 0 <= chl <= MCD_CHL_LOWEST_PRIORITY

} tas_pl1rsp_chl_subscribe_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_CHL_UNSUBSCRIBE
	uint8_t  chl;        // 0 <= chl < MCD_CHL_NUM_MAX
	uint8_t  reserved;   // 0
} tas_pl1rq_chl_unsubscribe_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_CHL_UNSUBSCRIBE
	uint8_t  chl;        // 0 <= chl < MCD_CHL_NUM_MAX
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR (unsubscribing an unsubscribed channel is no error)
} tas_pl1rsp_chl_unsubscribe_st;

typedef enum {  // channel option
	TAS_CHO_NONE = 0,
	TAS_CHO_INIT = 0x01,  // First word is the channel init value
} tas_cho_et;

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_CHL_MSG_C2D
	uint16_t reserved;   // 0

	uint8_t  chl;        // 0 <= chl < MCD_CHL_NUM_MAX
	uint8_t  cho;        // tas_cho_et
	uint16_t msg_length; // Includes the optional 4 bytes for init
} tas_pl1rq_chl_msg_c2d_st;  // Client to device channel message

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_CHL_MSG_D2C
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_DEV_RESET


	uint8_t  chl;        // 0 <= chl < MCD_CHL_NUM_MAX
	uint8_t  cho;        // tas_cho_et
	uint16_t msg_length; // Includes the optional 4 bytes for init
} tas_pl1rsp_chl_msg_d2c_st;  // Device to client channel message


typedef enum {  // Trace type
	TAS_TRC_T_UNKNOWN = 0,
	TAS_TRC_T_MTSC    = 1,
} tas_trc_type_et;
// Used in tas_server_info_st.supp_trc_type -> limited to 31 different trace types


typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_TRC_SUBSCRIBE
	uint16_t reserved;   // 0
	
	uint8_t  chso;       // tas_chso_et
	uint8_t  stream;
	uint16_t reserved1;  // 0

} tas_pl1rq_trc_subscribe_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_TRC_SUBSCRIBE
	uint8_t  reserved;   // 0
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_CMD_FAILED or TAS_PL_ERR_NOT_SUPPORTED

	uint8_t  chso;       // tas_chso_et
	uint8_t  stream;
	uint8_t  trct;       // tas_trc_type_et
	uint8_t  reserved1;  // 0

} tas_pl1rsp_trc_subscribe_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_TRC_UNSUBSCRIBE
	uint8_t  stream;
	uint8_t  reserved;   // 0
} tas_pl1rq_trc_unsubscribe_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_TRC_UNSUBSCRIBE
	uint8_t  stream;
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR (unsubscribing an unsubscribed stream is no error)
} tas_pl1rsp_trc_unsubscribe_st;

typedef enum {  // trace stream state
	TAS_TRCS_CONT     = 0,  // Trace stream continued
	TAS_TRCS_SYNC     = 1,  // Trace stream sync point for trace decoding (e.g. MTSC container)
	TAS_TRCS_START_AC = 2,  // Trace stream start after trace hardware (re)configuration
	TAS_TRCS_START_AR = 3,  // Trace stream start after an interruption by a reset
	TAS_TRCS_START_AI = 4,  // Trace stream start after an interruption by a trace system specific reason
} tas_trcs_et;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_TRC_DATA
	uint8_t  stream;
	uint8_t  trcs;        // tas_trcs_et
} tas_pl1rsp_trc_data_st;


typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL1_CMD_PL0_START
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  protoc_ver; // tas_pkt.h protocol version

	uint16_t pl1_cnt;    // Packet level 1 count returned by tas_pl1rsp_pl0_end_st
	uint16_t pl0_addr_map_mask; // Address maps used by this PL1 packet. Bit 15 represents TAS_AM15.

} tas_pl1rq_pl0_start_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_PL0_START
	uint8_t  con_id;     // Connection identifier of TasDispatcher
	uint8_t  err;        // TAS_PL_ERR_NO_ERROR, TAS_PL1_ERR_DEV_ACCESS, TAS_PL1_ERR_DEV_RESET
} tas_pl1rsp_pl0_start_st;  // Response



typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_PL0_END
	uint16_t num_pl0_rw; // Number of PL0 RW transactions
} tas_pl1rq_pl0_end_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL1_CMD_PL0_END
	uint16_t pl1_cnt;    // Packet level 1 count from tas_pl1rq_pl0_start_st
} tas_pl1rsp_pl0_end_st;  // Response




typedef struct {
	uint8_t  wl;         // Word Length of packet excluding this first word
	uint8_t  cmd;        // TAS_PL0_CMD_xxx
} tas_pl0rq_header_st;


// Packet level 0 tool request
typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL0_CMD_ACCESS_MODE
	uint16_t acc_mode;   // tas_pl0_acc_mode_et
} tas_pl0rq_acc_mode_st;
// Response: none (can cause a TAS_PL0_ERR_ACC_MODE for following transaction)

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL0_CMD_ADDR_MAP
	uint8_t  addr_map;   // 0 is default for device access. Refer also to TAS_AM15.
	uint8_t  reserved;   // 0
} tas_pl0rq_addr_map_st;
// Response: none (can cause a TAS_PL0_ERR_ADDR_MAP for following transaction)

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL0_CMD_BASE_ADDR32
	uint16_t ba31to16;
} tas_pl0rq_base_addr32_st;
// Response: none

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL0_CMD_BASE_ADDR64
	uint16_t ba31to16;

	uint32_t ba63to32;
} tas_pl0rq_base_addr64_st;
// Response: none

typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL0_CMD_WR8, TAS_PL0_CMD_WR16, TAS_PL0_CMD_WR32
	uint16_t a15to0;

	uint32_t data;
} tas_pl0rq_wr_st;
// Response: tas_pl0rsp_wr_st

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL0_CMD_RD8, TAS_PL0_CMD_RD16, TAS_PL0_CMD_RD32, TAS_PL0_CMD_RD64
	uint16_t a15to0;
} tas_pl0rq_rd_st;
// Response: tas_pl0rsp_rd_st

typedef struct {
	uint8_t  wl;         // 2
	uint8_t  cmd;        // TAS_PL0_CMD_WR64
	uint16_t a15to0;

	uint32_t data[2];
} tas_pl0rq_wr64_st;
// Response: tas_pl0rsp_wr_st

typedef struct {
	uint8_t  wl;         // N (0 means 256)
	uint8_t  cmd;        // TAS_PL0_CMD_WRBLK
	uint16_t a15to0;

	// Followed by 1 to 256 (1KB) data words
} tas_pl0rq_wrblk_st;
// Response: tas_pl0rsp_wr_st

typedef struct {
	uint8_t  wl;         // 3
	uint8_t  cmd;        // TAS_PL0_CMD_FILL
	uint16_t a15to0;

	uint8_t  wlwr;        // N (0 means 256) data words to be read
	uint8_t  reserved[3]; // 0

	uint64_t value;
} tas_pl0rq_fill_st;
// Response: tas_pl0rsp_wr_st


typedef struct {
	uint8_t  wl;         // 1
	uint8_t  cmd;        // TAS_PL0_CMD_RDBLK
	uint16_t a15to0;

	uint8_t  wlrd;        // N (0 means 256) data words to be read
	uint8_t  reserved[3]; // 0
} tas_pl0rq_rdblk_st;
// Response: tas_pl0rsp_rd_st or tas_pl0rsp_rdblk1kb_st


// Packet level 0 device response
typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL0_CMD_xxx
	uint8_t  reserved;   // 0   
	uint8_t  err;        // tas_pl0_err_et
} tas_pl0rsp_st;

typedef struct {
	uint8_t  wl;         // 0
	uint8_t  cmd;        // TAS_PL0_CMD_WRxx
	uint8_t  wlwr;       // 1 for wr, 2 for wr64, N for wrblk (0 means 256 if no error) data words written. 
	uint8_t  err;        // tas_pl_err_et
} tas_pl0rsp_wr_st;

typedef struct {
	uint8_t  wl;         // 0 or 1|2 or N depeding on err or rd8/16/32/64 or rdblk
	uint8_t  cmd;        // TAS_PL0_CMD_RDxx
	uint8_t  wlrd;       // 0 or 1|2 or N depeding on err or rd8/16/32/64 or rdblk
	uint8_t  err;        // tas_pl_err_et

	// Followed by 0 to 255 data words. tas_pl0rsp_rdblk1kb_st is used for 256 data words
} tas_pl0rsp_rd_st;

typedef struct {
	uint8_t  wl;         // EXCEPTION: 0 means 256 words for TAS_PL0_CMD_RDBLK1KB
	uint8_t  cmd;        // TAS_PL0_CMD_RDBLK1KB
	uint8_t  wlrd;       // 0 means 256 words
	uint8_t  err;        // TAS_PL0_ERR_NO_ERROR

	// Followed by 256 data words for 1KB
} tas_pl0rsp_rdblk1kb_st;



#ifdef __cplusplus
}
#endif

#endif   // __tas_pkt_h
