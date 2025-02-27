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

#include "tas_client_rw_base.h"
#include "tas_client_server_con.h"

#include <assert.h>

class CTasClientRw : public CTasClientRwBase, public CTasClientServerCon
{
public:

	tas_return_et session_start(const char* identifier, const char* session_name = "", const char* session_pw = "")
	{
		tas_return_et ret = mSessionStart(TAS_CLIENT_TYPE_RW, identifier, session_name, session_pw);

		assert(mTphRw == nullptr);
		if (ret == TAS_ERR_NONE) {
			mTphRw = new CTasPktHandlerRw(&mEi, get_con_info());
		}
		return ret;
	}

	bool device_reset_occurred()
	{
		if (!mSessionStarted) {
			return false;
		}

		uint32_t resetCount = mTphRw->get_device_reset_count();

		if (mDeviceResetCount > resetCount) {
			assert(mDeviceResetCount == ~0);  // device_connect() was not called
			assert(false);  // Wrong usage
			return false;
		}

		bool resetOccurred = (resetCount > mDeviceResetCount);

		mDeviceResetCount = resetCount;

		return resetOccurred;
	}

	tas_return_et device_connect(tas_clnt_dco_et dco)
	{
		tas_return_et ret = mDeviceConnect(dco);
		if (mTphRw)
			mDeviceResetCount = mTphRw->get_device_reset_count();
		return ret;
	}

	CTasClientRw(const char* client_name)
		: CTasClientServerCon(client_name, &mEi)
		, CTasClientRwBase(CTasPktHandlerRw::PKT_BUF_SIZE_DEFAULT)
	{
		mMbIfRw = mMbSocket;
		mMbIfRw->config(mTimeoutMs, CTasPktHandlerRw::PKT_BUF_SIZE_DEFAULT);
	};

	// Only needed for testing purposes. Not for regular TAS clients
	CTasClientRw(CTasPktMailboxIf* mb_if, uint32_t max_rq_size, uint32_t max_rsp_size, uint32_t max_num_rw)
		: CTasClientServerCon("TestOnly", &mEi)
		, CTasClientRwBase(mb_if, max_rq_size, max_rsp_size, max_num_rw)
	{
		mMbIf = mb_if;
		mSessionStarted = true;
	};

};
