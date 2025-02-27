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

#include "tas_client.h"
#include "tas_client_impl.h"

#include <memory>
#include <cstring>


class CTasPktHandlerBase
{

public:

	CTasPktHandlerBase(tas_error_info_st* ei);

	const uint32_t* get_pkt_rq_ping(tas_pl_cmd_et cmd);
	tas_return_et   set_pkt_rsp_ping(tas_pl_cmd_et cmd, tas_client_type_et client_type, const uint32_t* pkt_rsp);

	void set_con_info(const tas_con_info_st* con_info) { memcpy(&mConInfo, con_info, sizeof(tas_con_info_st)); }
	// Initial setting of con_info with the data from CTasClientServerCon

	const tas_con_info_st* get_con_info() { return &mConInfo; }

	uint32_t get_device_reset_count() { return mDeviceResetCount; };

protected:

	tas_return_et mHandlePktError(const uint32_t* pkt_rsp, tas_pl_cmd_et cmd);
	tas_return_et mSetPktRspErrConnectionProtocol();
	tas_return_et mSetPktRspErrDeviceAccess();

	tas_error_info_st* mEip;  // Pointer to single object in primary client class

	enum { PROTOC_VER = TAS_PKT_PROTOC_VER_1 };  // tas_pkt.h protocol version implemented in this class

	// This needs to be allocated and set in the derived class:
	uint32_t* mRqBuf;  // For one or more PL2 packet
	uint32_t mMaxRqSize, mMaxRspSize;  // Can be more than one PL2 packet
	uint32_t mRqWiMax;

	uint32_t mRqBufWi; // Word index

	tas_con_info_st mConInfo;

	uint16_t mDeviceConnectOption;

	uint16_t mPl1CntOutstandingOldest;  // Cnt of first outstanding request
	uint16_t mPl1CntOutstandingLast;    // Cnt of last outstanding request

	uint32_t mDeviceResetCount;

private:

	virtual void mEnforceDerivedClass() = 0;  // Pure virtual method enforce that only used in derived RW or CHL class

};