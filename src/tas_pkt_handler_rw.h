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

#include "tas_pkt_handler_base.h"

class CTasPktHandlerRw : public CTasPktHandlerBase
{

public:

	CTasPktHandlerRw(tas_error_info_st* ei, const tas_con_info_st* con_info);
	// TasServer connection was established with CTasClientServerCon before
	// Uses default settings with 64KB for rq and rsp and 256 for max_num_rw.
	// Please note that the effective data sizes are lower since these limits include the
	// packet overhead which depends on the transaction data sizes and address alignment
	// and the TAS frontend properties.

	CTasPktHandlerRw(tas_error_info_st* ei, uint32_t max_rq_size, uint32_t max_rsp_size, uint32_t max_num_rw);
	// Used for testing and inside of TasServer
	// Controls the allocated memory for packets and transaction descriptions.

	~CTasPktHandlerRw();

	// This API assumes a usage where:
	// Normally all transactions are successfull
	// Errors are not handled individually for the transactions

	// Create packets option 1:
	void rw_start();
	bool rw_add_rd(uint64_t addr, uint32_t num_bytes,       void* data, uint16_t acc_mode = 0, uint8_t addr_map = 0);
	bool rw_add_wr(uint64_t addr, uint32_t num_bytes, const void* data, uint16_t acc_mode = 0, uint8_t addr_map = 0);
	bool rw_add_fill(uint64_t addr, uint32_t num_bytes, uint64_t value, uint16_t acc_mode = 0, uint8_t addr_map = 0);
	// The functions return false and do not add, if the limits (default or set by constructor) are violated
	// However created packets up to this point stay valid. This supports a simple loop for splitting larger data accesses.

	// Create packets option 2:
	bool rw_set_trans(const tas_rw_trans_st* trans, uint32_t num_trans = 1);
	// Returns false if limits (default or set by constructor) are violated.
	// No packets are created in this case.

	uint32_t rw_get_rq_size();   // Returns the size of all PL2 request packets
	uint32_t rw_get_rsp_size();  // Returns the predicted size of all PL2 response packets (can be smaller in case of errors)
	// If both are <= tas_con_info_st.max_pl2rq_pkt_size, max_pl1rqsp_pkt_size respectively only one PL2 packet is generated
	// This means execution atomicity is warranted. This can be checked by num_pl2_pkt with rw_get_rq().

	// Finalize and get request packet(s)
	void rw_get_rq(const uint32_t** rq, uint32_t* rq_num_bytes, uint32_t* rsp_num_bytes_max, uint32_t* num_pl2_pkt);
	// In case of read errors the rsp size can be smaller

	uint32_t rw_get_num_pl2_pkt(const uint32_t* rsp, uint32_t num_bytes);
	// Check if received response contains already all PL2 packets
	// Note that the response packet(s) can be smaller than predicted by rsp_num_bytes if there are read errors

	// Set received response packet(s)
	tas_return_et rw_set_rsp(const uint32_t* rsp, uint32_t num_bytes);
	// num_bytes will be smaller than rsp_num_bytes from rw_get_rq() in case of errors

	uint32_t rw_get_trans_rsp(const tas_rw_trans_rsp_st** trans_rsp);
	// Returns the number of RW transactions
	// trans_rsp[] contains the response
	// This method is for individual error handling or debugging

	uint32_t rw_get_pl0_trans(const tas_rw_trans_st** pl0_trans, const tas_rw_trans_rsp_st** pl0_trans_rsp);
	// Returns the number of transactions on PL0 level
	// pl0_trans is the same as trans_rsp if no transaction was split into different PL2 packets
	// pl0_trans_rsp[] contains the response
	// This method is only for debugging

	enum {
		PKT_BUF_SIZE_DEFAULT = 0x10000,
		MAX_NUM_RW_DEFAULT = 256,
		BUF_ALLOWANCE = 64,
	};   // Limits are for all generated PL2 packets together

private:

	void mInit(uint32_t max_rq_size, uint32_t max_rsp_size, uint32_t max_num_rw);

	void mEnforceDerivedClass() { ; }

	void mPl2PktInit();
	void mPktAdd_SetAddrMapAccModeBaseAddr(uint8_t addr_map, uint16_t acc_mode, uint64_t addr);
	void mPktAdd_Rd(uint64_t addr, uint32_t num_bytes, void* data, uint16_t acc_mode, uint8_t addr_map);
	void mPktAdd_Wr(uint64_t addr, uint32_t num_bytes, const void* data, uint16_t acc_mode, uint8_t addr_map);
	void mPktAdd_Fill(uint64_t addr, uint32_t num_bytes, uint64_t value, uint16_t acc_mode, uint8_t addr_map);
	bool mCheckRemainingPktSizeSufficient(uint32_t num_bytes_needed_pktrq, uint32_t num_bytes_needed_pktrsp)
	{
		if (num_bytes_needed_pktrq > mGetRemainingSizeInPktRq())
			return false;
		else if (num_bytes_needed_pktrsp > mGetRemainingSizeInPktRsp())
			return false;
		return true;
	}
	void mPktFinalizeIfNeeded(uint32_t num_bytes_needed_pktrq, uint32_t num_bytes_needed_pktrsp) {
		if (!mCheckRemainingPktSizeSufficient(num_bytes_needed_pktrq, num_bytes_needed_pktrsp))
			mPktFinalize();
	}
	void mPktFinalize(bool init_next_pl2_pkt = true);

	uint32_t mGetNumBytesAddrMapAccModeBaseAddr(uint8_t addr_map, uint16_t acc_mode, uint64_t addr);

	bool mCheckLimits(uint32_t num_bytes_rd, uint32_t num_bytes_wr);
	bool mCheckAddrMapRulesInPkt(uint8_t addr_map);
	bool mNumTransManageableRd(uint64_t addr, uint32_t num_bytes);
	bool mNumTransManageableWr(uint64_t addr, uint32_t num_bytes);

	uint32_t mGetRemainingSizeInPktRq();
	uint32_t mGetRemainingSizeInPktRsp();
	uint32_t mGetWrDataBlkSizeInPktRq(uint32_t num_bytes, uint64_t addr);
	uint32_t mGetRdDataBlkSizeInPktRsp(uint32_t num_bytes);

	tas_return_et mSetPktRspErrPl1Cnt();
	void mSetPktRspErrPl0Data(uint8_t pl_err, tas_return_et tas_err, uint64_t addr, uint8_t addr_map);

	enum { PROTOC_VER = 0 };  // TasPkt protocol version implemented in this class

	uint32_t mNumPl2Pkt;

	uint32_t  mPl2HdrWi;  // Word index of start of current PL2 packet
	tas_pl1rq_pl0_start_st* mPl0Start;  // PL0 start of current PL2 packet
	uint32_t mPl2NumTrans;  // Number of RW transactions in current PL2 packet

	uint32_t mMaxWrDataBlkSizeInPktRq, mMaxRdDataBlkSizeInPktRsp;  // Depends on mConInfo

	uint32_t mRspSize;         // Overall size of the PL2 packets [bytes]
	uint32_t mPl2RspPktStart;  // Start of current PL2 packet [bytes|

	uint16_t mPl0AccMode;
	uint8_t  mPl0AddrMap;
	uint16_t mPl0AddrMapMask;  // Address maps used by this PL1 packet. Bit 15 represents TAS_AM15.
	uint64_t mPl0BaseAddr;

	// Transactions on API level, determined by caller
	tas_rw_trans_st* mRwTrans;
	tas_rw_trans_rsp_st* mRwTransRsp;
	uint32_t mRwNumTrans;   // Used as index for mRwTrans[] and mRwTransRsp[]

	// Resulting transactions on PL0 level
	tas_rw_trans_st* mPl0Trans;
	tas_rw_trans_rsp_st* mPl0TransRsp;
	uint32_t mPl0NumTrans;   // Used also as index for mPl0Trans[] and mPl0TransRsp[]

	uint32_t mNumTransMax;  // mRwNumTrans <= mPl0NumTrans

	bool mGetPktRqWasCalled;
};
