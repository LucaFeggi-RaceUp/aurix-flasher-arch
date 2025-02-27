/*
 * ********************************************************************************************************************
 *  Copyright 2022 Infineon Technologies AG
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
#ifndef __tas_chl_h
#define __tas_chl_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*

Optimization: Avoid wrap around message data is buffer is empty - DONE

Tool reads base address from COMDATA in RW mode (enables DAPE in A3G)
All tool accesses shall use block reads/writes

Standardize some channel numbers:
File IO

TCH communication structs

Device SW configures DAPE and COMDATA interrupt

osw_ Ownership by SW
otl_ Ownership by tool
stcs_ Set by tool, cleared by SW

Reserve channel 31 for internal purposes
Can implement an RW ECF in the device
ECF actively offers this feature to the tool by a TRM init message
An external server has just a TCHS connection to the device and unses then channel 31 for the RW accesses from the different clients
Client can read the configuration e.g. permitted address windows

Idea: SW gives description of SRN to use: address + value to be written
This is usable for pre TC4D and also for the new feature of 2 ISR trigger bits in CBS (Jira 0000064372-12)

*/

#define TAS_CHL_OSW_CONFIG_SIGNATURE  0x0A0B0C0D

typedef struct {  // SW owned, static channel buffer description
	union {
		struct {
			uint64_t  buf_ptr;   // Pointer to buffer stored as value for 64 bit devices
		} a64;                   // 64 bit architectures
		struct {
			uint32_t buf_ptr;    // Pointer to buffer stored as value
			uint32_t signature;  // TAS_CHL_OSW_CONFIG_SIGNATURE
		} a32;                   // 32 bit architectures
	};
	uint16_t  buf_size;          // Size of the buffer. Must be an even fraction of 256KB
	uint8_t   max_num_msg;       // Maximum number of messages in the buffer
	uint8_t   max_msg_size_w32;  // Maximum size of one message [32 bit words]
	uint32_t  reserved;
} tas_chl_osw_buf_des_st;

typedef struct {  // Static configuration 
	tas_chl_osw_buf_des_st rcv_buf;   // Receive (SW input) buffer description
	tas_chl_osw_buf_des_st trm_buf;   // Transmit (SW output) buffer description
	uint32_t  srn_addr;                 // SRN address. 0 if operation is by SW polling
	uint32_t  ipv4_addr;  // IPV4 address of the device which can be read via DAP
} tas_chl_osw_config_st;

typedef struct {  // Control 
	uint32_t otl_chl_sel_trm;  // Channels be individually subscribed by the tool
} tas_chl_ctrl_st;

typedef struct {
	union {
		struct {
			uint16_t w32a_start;  // 32 bit word address for message start within buffer
			uint16_t chl_size;    // Bit[9:0] msg_size [byte] 0 is 1024, bit[14:10] channel number, bit[15] init_flag
		} u16;
		uint32_t u32;
	};
} tas_chl_msg_des_st;

typedef struct {
	union {
		struct {
			uint16_t  rcv_step_count;  // New counter value indicates that a new rcv_msg_des is consistent and valid
			uint16_t  trm_w32a_next;   // Next address in buf_trm, that will be read by tool if data is available.
		} u16;
		uint32_t u32;
	};
} tas_chl_otl_ctrl_trail_st;

typedef struct {
	union {
		struct {
			uint16_t  trm_step_count;  // New counter value indicates that a new trm_msg_des is consistent and valid
			uint16_t  rcv_w32a_next;   // Next address in buf_rcv, provided to tool for writing if buffer space and data is available.
		} u16;
		uint32_t u32;
	};
} tas_chl_osw_ctrl_trail_st;



inline int tas_chl_get_msg_des_rcv_offset_addr()
{
	return sizeof(tas_chl_osw_config_st) + sizeof(tas_chl_ctrl_st);
}

inline int tas_chl_get_msg_des_trm_offset_addr(const tas_chl_osw_config_st* osw_config)
{
	return tas_chl_get_msg_des_rcv_offset_addr() + (osw_config->rcv_buf.max_num_msg + 1) * sizeof(uint32_t);
}

inline uint8_t tas_chl_msg_des_get_chl(const tas_chl_msg_des_st* msg_des)
{
	return (uint8_t)((msg_des->u16.chl_size >> 10) & 0x1F);
}

inline uint16_t tas_chl_msg_des_get_chl_init(const tas_chl_msg_des_st* msg_des)
{
	return msg_des->u16.chl_size & 0x8000;
}

inline uint16_t tas_chl_msg_des_get_size(const tas_chl_msg_des_st* msg_des)
{
	uint16_t size = msg_des->u16.chl_size & 0x3FF;
	return (size == 0) ? 1024 : size;
}

inline uint16_t tas_chl_msg_des_get_w32_size(const tas_chl_msg_des_st* msg_des)
{
	return (tas_chl_msg_des_get_size(msg_des) + 3) / 4;
}

typedef struct {
	tas_chl_osw_config_st* osw_config;
	tas_chl_ctrl_st* ctrl;
	tas_chl_msg_des_st* rcv_msg_des;
	tas_chl_otl_ctrl_trail_st* otl_trail;
	tas_chl_msg_des_st* trm_msg_des;
	tas_chl_osw_ctrl_trail_st* osw_trail;
} tas_chl_ptr_st;

enum
{
	TCHS_MAX_NUM_CHL = 32,          // Channels can be individually subscribed by otl_chl_sel_trm
	TCHS_MAX_MSG_SIZE = 1024,       // Absolute maximum msg size. Usually further reduced with max_msg_size_w32
	TCHS_MAX_NUM_MSG_BUF_CHL = 4,	// Maximum number of buffered messages per channel
	TCHS_MAX_NUM_MSG_BUF_DEV = 32,  // Maximum number of buffered messages in the device
};

inline int32_t tas_chl_diff_mod16bit(uint16_t vs, uint16_t vl)  // Substract a smaller from a larger value considering 16 bit modulo overruns
{
	if ((vs > 0xF000) && (vl < 0x1000)) {  // Modulo 16 bit overrun
		return 0x10000 - (vs - vl);
	}
	if ((vl > 0xF000) && (vs < 0x1000)) {  // Modulo 16 bit overrun
		return (vl - vs) - 0x10000;
	}
	return vl - vs;
}

inline int tas_chl_check_tas_chl_st(const tas_chl_ptr_st* tchsPtr, uint8_t tas_chl_init_state)
{
	const int errorRetValue = 0;
	const int noErrorRetValue = 1;

	// Check some basic design assumptions
	if (sizeof(tas_chl_msg_des_st) != sizeof(uint32_t))
		return errorRetValue;

	// Check tchs
	tas_chl_osw_buf_des_st* rcv = &tchsPtr->osw_config->rcv_buf;
	tas_chl_osw_buf_des_st* trm = &tchsPtr->osw_config->trm_buf;
	if (rcv->buf_size % 4) return errorRetValue;
	if (trm->buf_size % 4) return errorRetValue;
	if (rcv->max_num_msg == 0) return errorRetValue;
	if (trm->max_num_msg == 0) return errorRetValue;
	if (rcv->max_num_msg > TCHS_MAX_NUM_MSG_BUF_DEV) return errorRetValue;
	if (trm->max_num_msg > TCHS_MAX_NUM_MSG_BUF_DEV) return errorRetValue;
	if (rcv->max_msg_size_w32 < 4) return errorRetValue;  // Unreasonable max messages size (less than 16 bytes)
	if (trm->max_msg_size_w32 < 4) return errorRetValue;  // Unreasonable max messages size (less than 16 bytes)
	if (rcv->max_msg_size_w32 > TCHS_MAX_MSG_SIZE / 4) return errorRetValue;
	if (trm->max_msg_size_w32 > TCHS_MAX_MSG_SIZE / 4) return errorRetValue;
	if (rcv->max_msg_size_w32 * 4 * rcv->max_num_msg < rcv->buf_size) return errorRetValue;  // Buffer can never be full
	if (trm->max_msg_size_w32 * 4 * trm->max_num_msg < trm->buf_size) return errorRetValue;  // Buffer can never be full

	if (tas_chl_init_state) {
		if (tchsPtr->ctrl->otl_chl_sel_trm != 0) return errorRetValue;

		uint8_t im;
		for (im = 0; im < tchsPtr->osw_config->rcv_buf.max_num_msg; im++) {
			if (tchsPtr->rcv_msg_des[im].u32 != 0) return errorRetValue;
		}
		if (tchsPtr->rcv_msg_des[im].u32 != 0) return errorRetValue;  // This is the following u32_reserved word which includes otl_trail

		for (im = 0; im < tchsPtr->osw_config->trm_buf.max_num_msg; im++) {
			if (tchsPtr->trm_msg_des[im].u32 != 0) return errorRetValue;
		}
		if (tchsPtr->trm_msg_des[im].u32 != 0) return errorRetValue;  // This is the following u32_reserved word which includes osw_trail
	}

	return noErrorRetValue;
}

#ifdef __cplusplus
}
#endif

#endif // __tas_chl_h
