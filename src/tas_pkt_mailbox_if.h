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

#include <stdint.h>

struct CTasPktMailboxIf
{

public:

	virtual void config(uint32_t timeout_receive_ms, uint32_t max_num_bytes_rsp) = 0;

	virtual bool connected() = 0;

	virtual bool send(const uint32_t* rq, uint32_t num_pl2_pkt = 1) = 0;
	// Call is blocking until all PL2 packets have been sent
	// Returns false on error

	virtual bool receive(uint32_t* rsp, uint32_t* num_bytes_rsp) = 0;
	// Blocking until a packet is received or a timeout occurred
	// Returns false on error. Timeout is no error!

	virtual bool execute(const uint32_t* rq, uint32_t* rsp, uint32_t num_pl2_pkt = 1, uint32_t* num_bytes_rsp = nullptr) = 0;
	// Blocking until all PL2 packets have been sent and received or a timeout occurred
	// If num_pl2_pkt = 1, rq is a single PL2 packet. In this case num_bytes_rsp is not needed as well.
	// Returns false on error. Timeout is an error.

};