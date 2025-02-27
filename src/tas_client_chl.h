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
#include "tas_client_server_con.h"
#include "tas_pkt_handler_chl.h"
#include "tas_pkt_mailbox_if.h"


class CTasClientChl : public CTasClientServerCon
{

public:

	CTasClientChl(const char* client_name);

	tas_return_et session_start(const char* identifier, const char* session_name = "", const char* session_pw = "", 
								tas_chl_target_et chl_target = TAS_CHL_TGT_DMM, uint64_t chl_param = 0);
	// A session can only be started when the channel description is available in the TasServer.
	// The channel description is read from the device by the first ClientChl.session_start() call.
	// If this is not possible (e.g. device in halt after reset state), session_start() fails.
	// The TasServer forgets the channel description, when no ClientChl is connected to the target.

	tas_return_et subscribe(uint8_t chl, tas_cht_et cht, tas_chso_et chso = TAS_CHSO_EXCLUSIVE, uint8_t* prio = nullptr);
	// The channel number chl can be between 0 and 31
	// The channel type can be send, receive or bidirectional
	// A channel can be claimed as exclusive (no other client can subscribe anymore)
	// Claiming will fail if the channel was already subscribed by another client
	// For prioritized channels 0 is highest and TAS_CHL_LOWEST_PRIORITY lowest priority
	// Priorities can only be assigned to one channel except the lowest priority
	// prio [in]  : Requested priority (default TAS_CHL_LOWEST_PRIORITY)
	// prio [out] : Assigned priority (equal or lower than requested)
	// It is not possible to subscribe to more than one channel

	tas_return_et unsubscribe();

	tas_return_et send_msg(const void* msg, uint16_t msg_length, uint32_t init = 0);
	// tas_con_info_st.msg_length_c2d sets the limit for msg_lengh plus 4 bytes for init if init is not 0

	tas_return_et rcv_msg(uint32_t timeout_ms, const void** msg, uint16_t* msg_length, uint32_t* init);
	// Blocking function with timeout. Timeout can be 0 for non-blocking.
	// tas_con_info_st.msg_length_d2c sets the limit for msg_lengh plus 4 bytes for init if init is not 0

	bool device_reset_occurred()
	{
		if (!mSessionStarted) {
			return false;
		}

		uint32_t resetCount = mTphChl.get_device_reset_count();

		if (mDeviceResetCount > resetCount) {
			assert(mDeviceResetCount == ~0U);  // device_connect() was not called
			assert(false);  // Wrong usage
			return false;
		}

		bool resetOccurred = (resetCount > mDeviceResetCount);

		mDeviceResetCount = resetCount;

		return resetOccurred;
	}

	tas_return_et device_connect(tas_clnt_dco_et dco);
	// Can only be called when no channel is subscribed

	// The following methods are only needed for special use cases and debugging

	tas_return_et target_ping(tas_con_info_st* con_info);
	// Checks the connection which was established with session_start()
	// The channel description will be read from the device only once if the channel information is present

	CTasClientChl(CTasPktMailboxIf* mb_if);
	// Only used for special test setups

private:

	tas_error_info_st mEi;

	CTasPktMailboxIf* mMbIf;

	CTasPktHandlerChl mTphChl;

	tas_cht_et mChlCht = TAS_CHT_NONE;
	uint8_t    mChlNum = TAS_CHL_NUM_MAX;

	uint32_t mRcvMsgBuf[TAS_PL1_CHL_MAX_MSG_SIZE / 4];

};