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

class CTasPktHandlerTrc : public CTasPktHandlerBase
{

public:

	CTasPktHandlerTrc(tas_error_info_st* ei);

	const uint32_t* get_pkt_rq_subscribe(uint8_t stream, tas_chso_et chso);
	// Number of bytes is pkt_rq[0]
	tas_return_et set_pkt_rsp_subscribe(const uint32_t* pkt_rsp, tas_trc_type_et *trct, tas_chso_et* chso);

	const uint32_t* get_pkt_rq_unsubscribe(uint8_t stream);
	// Number of bytes is pkt_rq[0]
	tas_return_et set_pkt_rsp_unsubscribe(const uint32_t* pkt_rsp);

	tas_return_et set_pkt_rcv_trace(const uint32_t* pkt_rsp, const void** trace_data, uint32_t* length, tas_trcs_et* trcs, uint8_t* stream);


private:

	void mEnforceDerivedClass() { ; }

	tas_return_et mSetPktRspErrTraceClaimed(uint8_t stream);
	tas_return_et mSetPktRspErrTraceNotSupported();

	uint8_t mStream;    // Check response of subscribe/unsubscribe
	tas_chso_et mChso;  // Check response of subscribe

};