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
#include "tas_pkt_handler_trc.h"
#include "tas_pkt_mailbox_if.h"


class CTasClientTrc
{

public:

	CTasClientTrc();

	tas_return_et subscribe(tas_trc_type_et* trct, uint8_t stream = 0, tas_chso_et chso = TAS_CHSO_DEFAULT);
	// stream optional allows to differentiate between independent trace streams from the same device

	tas_return_et unsubscribe(uint8_t stream = 0);

	tas_return_et rcv_trace(uint32_t timeout_ms, const void** trace_data, uint32_t *length, tas_trcs_et* trcs, uint8_t* stream = nullptr);
	// Blocking function with timeout.


	// The following methods are only needed for special use cases and debugging

	tas_return_et target_ping(tas_con_info_st* con_info);
	// Check the connection which was established with CTasClientServerCon::session_start() before

	CTasClientTrc(CTasPktMailboxIf* mb_if);
	// Only used for special test setups

private:

	tas_error_info_st mEi;

	CTasPktMailboxIf* mMbIf;

	CTasPktHandlerTrc* mTphTrc;

};