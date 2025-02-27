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

class CTasPktHandlerChl : public CTasPktHandlerBase
{

public:

	CTasPktHandlerChl(tas_error_info_st* ei);
	~CTasPktHandlerChl();

	const uint32_t* get_pkt_rq_subscribe(uint8_t chl, tas_cht_et cht, tas_chso_et chso, uint8_t prio);
	// Number of bytes is pkt_rq[0]
	tas_return_et set_pkt_rsp_subscribe(const uint32_t* pkt_rsp, tas_cht_et* cht, tas_chso_et* chso, uint8_t *prio);

	const uint32_t* get_pkt_rq_unsubscribe(uint8_t chl);
	// Number of bytes is pkt_rq[0]
	tas_return_et set_pkt_rsp_unsubscribe(const uint32_t* pkt_rsp);

	const uint32_t* get_pkt_send_msg(uint8_t chl, const void* msg, uint16_t msg_length, uint32_t init);
	// Number of bytes is pkt_rq[0]

	tas_return_et set_pkt_rcv_msg(const uint32_t* pkt_rsp, uint8_t chl, const void** msg, uint16_t* msg_length, uint32_t* init);

private:

	void mEnforceDerivedClass() { ; }

	uint8_t mChl;       // Check response of subscribe/unsubscribe
	tas_cht_et mCht;    // Check response of subscribe
	tas_chso_et mChso;  // Check response of subscribe

};