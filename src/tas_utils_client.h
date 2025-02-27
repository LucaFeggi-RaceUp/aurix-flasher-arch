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
#include <cstring>

inline tas_return_et tasutil_userpins_set_high(CTasClientRw* tcrw, uint32_t pins)
{
	tas_userpins_mask_st up = { pins, pins };
	return tcrw->write64(TAS_AM15_RW_USERPINS, *(uint64_t*)&up, TAS_AM15);
}

inline tas_return_et tasutil_userpins_set_low(CTasClientRw* tcrw, uint32_t pins)
{
	tas_userpins_mask_st up = { 0, pins };
	return tcrw->write64(TAS_AM15_RW_USERPINS, *(uint64_t*)&up, TAS_AM15);
}

inline tas_return_et tasutil_acc_hw_runled_on(CTasClientRw* tcrw)
{
	return tasutil_userpins_set_low(tcrw, TAS_UP_RUNLED);
}

inline tas_return_et tasutil_acc_hw_runled_off(CTasClientRw* tcrw)
{
	return tasutil_userpins_set_high(tcrw, TAS_UP_RUNLED);
}

inline bool tasutil_emulator_connected(CTasClientServerCon* client)
{
	return (strstr(client->get_con_info()->identifier, "Emulator") != NULL);;
}


