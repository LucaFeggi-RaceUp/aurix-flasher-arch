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
#pragma once

#include "tas_pkt.h"
#include <stdint.h>

#define TAS_INFO_STR_LEN  256     

enum tas_return_et : uint16_t {
	TAS_ERR_NONE             = 0,        // No error

	TAS_ERR_GENERAL          = 0x0F00,   // General error. E.g. unexpected behavior of the TasServer

	TAS_ERR_FN_NOT_SUPPORTED = 0x0100,   // Function is e.g. not implemented
	TAS_ERR_FN_USAGE         = 0x0110,   // TAS API not correctly used
	TAS_ERR_FN_PARAM         = 0x0120,   // Caller passed an invalid parameter

	TAS_ERR_SERVER_CON       = 0x0200,   // Server connection error
	TAS_ERR_SERVER_LOCKED    = 0x0210,   // Server is locked

	TAS_ERR_DEVICE_ACCESS    = 0x0400,   // Cannot access device (power-down, reset active, etc.)
	TAS_ERR_DEVICE_LOCKED    = 0x0410,   // Device is locked

	TAS_ERR_RW_READ          = 0x0600,   // Read access failed
	TAS_ERR_RW_WRITE         = 0x0610,   // Write access failed

	TAS_ERR_CHL_SETUP        = 0x0800,   // Channel setup failed
	TAS_ERR_CHL_SEND         = 0x0810,   // Sending of the message has failed (e.g. buffer full). Can try again.
	TAS_ERR_CHL_RCV          = 0x0820,   // No message was received. Can try again.

	TAS_ERR_TRC_RCV          = 0x0A00,   // No trace data was received. Can try again.
};

enum tas_clnt_dco_et : uint16_t {  // device_connect() option
	TAS_CLNT_DCO_HOT_ATTACH     = 0,
	TAS_CLNT_DCO_RESET          = TAS_DEV_CON_FEAT_RESET,
	TAS_CLNT_DCO_RESET_AND_HALT = TAS_DEV_CON_FEAT_RESET_AND_HALT,
	TAS_CLNT_DCO_UNKNOWN        = TAS_DEV_CON_FEAT_UNKNOWN,        // Connect to "unknown" device -> no device interaction
	TAS_CLNT_DCO_UNKNOWN_RESET  = TAS_DEV_CON_FEAT_UNKNOWN_RESET,  // Reset "unknown" device -> no device interaction
};

enum tas_rw_trans_type_et : uint8_t {
	TAS_RW_TT_RD   = 1,
	TAS_RW_TT_WR   = 2,
	TAS_RW_TT_FILL = 6,
};

struct tas_rw_trans_st {
	uint64_t addr;
	uint32_t num_bytes;
	uint16_t acc_mode;
	uint8_t  addr_map;
	tas_rw_trans_type_et type;
	union {
		const void* wdata;
		void* rdata;
	};
};

struct tas_rw_trans_rsp_st {
	uint16_t num_bytes_ok;
	tas_pl_err_et8 pl_err;
};
