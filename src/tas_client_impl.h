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

#include <assert.h>
#include <stdio.h>

#ifdef _DEBUG
enum { TAS_DEFAULT_TIMEOUT_MS = -1 };    // No timeout
#else
enum { TAS_DEFAULT_TIMEOUT_MS = 20000 }; // 20s
#endif

struct tas_error_info_st {
	char info[TAS_INFO_STR_LEN];
	tas_return_et tas_err;
};

inline tas_return_et tas_clear_error_info(tas_error_info_st* ei)
{
	ei->info[0] = 0;
	ei->tas_err = TAS_ERR_NONE;
	return TAS_ERR_NONE;
}

inline tas_return_et tas_client_handle_error_server_con(tas_error_info_st* ei)
{
	assert(false);
	snprintf(ei->info, TAS_INFO_STR_LEN, "ERROR: Server connection");
	ei->tas_err = TAS_ERR_SERVER_CON;
	return ei->tas_err;
}

