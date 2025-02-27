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

#include "tas_client_rw.h"

enum tasutil_jtag_scan_et : uint32_t {
	TJS_NONE = 0,
	TJS_TAP_RESET = 0x01,  // Initial TAP controller reset with state machine sequence
};  // Options for scans

struct tasutil_jtag_scan_st {
	tasutil_jtag_scan_et tjs;
	tas_jtag_set_ir_st   ir;   // If ir.width is 0 -> no IR update
	uint32_t        num_bits;  // Number of data scan bits
	const uint64_t* data_in;   // nullptr means zeros are shifted in
	uint64_t*       data_out;  // nullptr means output is ignored
};

tas_return_et tasutil_jtag_scan(CTasClientRw* tcrw, const tasutil_jtag_scan_st* scan, uint8_t num_scan);

