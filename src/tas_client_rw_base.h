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

#include "tas_client_impl.h"
#include "tas_pkt_mailbox_if.h"
#include "tas_pkt_handler_rw.h"
#include "tas_am15_am14.h"


class CTasClientRwBase
{

public:

	// This API assumes that the timout and the size and number of transactions are configured
	// in a way that no timeout will occur.
	// If a timeout occurs the server connection has to be setup again.

	CTasClientRwBase(uint32_t max_rsp_size);

	~CTasClientRwBase();

	tas_return_et read8(uint64_t addr, uint8_t* value, uint8_t addr_map = TAS_AM0);
	tas_return_et write8(uint64_t addr, uint8_t value, uint8_t addr_map = TAS_AM0);
	tas_return_et read16(uint64_t addr, uint16_t* value, uint8_t addr_map = TAS_AM0);
	tas_return_et write16(uint64_t addr, uint16_t value, uint8_t addr_map = TAS_AM0);
	tas_return_et read32(uint64_t addr, uint32_t* value, uint8_t addr_map = TAS_AM0);
	tas_return_et write32(uint64_t addr, uint32_t value, uint8_t addr_map = TAS_AM0);
	tas_return_et read64(uint64_t addr, uint64_t* value, uint8_t addr_map = TAS_AM0);
	tas_return_et write64(uint64_t addr, uint64_t value, uint8_t addr_map = TAS_AM0);

	tas_return_et read(uint64_t addr, void* data, uint32_t num_bytes, uint32_t* num_bytes_ok, uint8_t addr_map = TAS_AM0);
	tas_return_et write(uint64_t addr, const void* data, uint32_t num_bytes, uint32_t* num_bytes_ok, uint8_t addr_map = TAS_AM0);
	
	tas_return_et fill32(uint64_t addr, uint32_t value, uint32_t num_bytes, uint8_t addr_map = TAS_AM0);
	// addr and num_bytes need to be 32 bit aligned. addr_map has to be lower than TAS_AM12.

	tas_return_et fill64(uint64_t addr, uint64_t value, uint32_t num_bytes, uint8_t addr_map = TAS_AM0);
	// addr and num_bytes need to be 64 bit aligned. addr_map has to be lower than TAS_AM12.

	tas_return_et execute_trans(const tas_rw_trans_st* trans, uint32_t num_trans);
	// Use transaction arrays for higher efficiency and for ensuring atomicity of the execution
	// If trans contains a mixture of different address maps, the following rules apply:
	// 1. If all address maps are in TAS_AM_MASK_SHARED, the first transaction with an error
	//    will return this error. Following transactions will return TAS_PL0_ERR_CONSEQUENTIAL
	// 2. For TAS_AM_MASK_EXCLUSIVE the same applies for the single exclusive address map.
	// 3. If trans consists of sequences of transactions which follow rule 1 or 2, these
	//    rules are applied independently to these sequences of transactions
	// A TAS_RW_TT_FILL transaction needs to be 64 bit aligned (addr, num_bytes)

	// The following methods are only needed for special use cases and debugging

	tas_return_et target_ping(tas_con_info_st* con_info);
	// Check the connection which was established with CTasClientServerCon::session_start() before

	uint32_t rw_get_trans_rsp(const tas_rw_trans_rsp_st** trans_rsp);
	// Returns the number of RW transactions
	// trans_rsp[] is the response to trans or the single transaction from the other methods.
	// This method is for individual error handling or debugging

	void rw_set_timeout(uint32_t timeout_ms);
	// Default timeout is 10s. Recommended for TAS clients. No need to call in this case.
	// Please note that a timeout is fatal so the server connection has to be setup again.

	CTasClientRwBase(CTasPktMailboxIf* mb_if, uint32_t max_rq_size, uint32_t max_rsp_size, uint32_t max_num_rw);
	// Only used within the server and for special test setups

protected:

	tas_error_info_st mEi;

	uint32_t* mRspBuf;  // For one or more PL2 packet

	CTasPktMailboxIf* mMbIfRw;  // Needed in addition to mMbIf due to usage in TasServer

	CTasPktHandlerRw* mTphRw = nullptr;

	uint32_t mTimeoutMs;

private:

	tas_return_et mExecuteSingleTrans(const tas_rw_trans_st* trans, uint32_t* num_bytes_ok = nullptr);

};
