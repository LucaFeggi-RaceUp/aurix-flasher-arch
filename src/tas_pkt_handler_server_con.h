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

#include "tas_am15_am14.h"


class CTasPktHandlerServerCon : public CTasPktHandlerBase
{

public:

	CTasPktHandlerServerCon(tas_error_info_st* ei);
	~CTasPktHandlerServerCon();

	const uint32_t* get_pkt_rq_server_connect(const char* client_name, const char* user_name, uint32_t client_pid);
	tas_return_et   set_pkt_rsp_server_connect(const uint32_t* pkt_rsp, const tas_server_info_st** server_info, uint64_t* challenge);

	const uint32_t* get_pkt_rq_server_unlock(const void* key, uint16_t key_length);
	tas_return_et   set_pkt_rsp_server_unlock(const uint32_t* pkt_rsp);

	const uint32_t* get_pkt_rq_get_targets(uint8_t start_index);
	tas_return_et   set_pkt_rsp_get_targets(const uint32_t* pkt_rsp, uint8_t* num_target, uint8_t* num_now);
	void  get_target_info(const tas_target_info_st** target_info, uint32_t* num_target);

	const uint32_t* get_pkt_rq_get_target_clients(const char* identifier, uint8_t start_index);
	tas_return_et   set_pkt_rsp_get_target_clients(const uint32_t* pkt_rsp, uint8_t* num_client, uint8_t* num_now);
	void  get_target_clients_info(const char** session_name, uint64_t* session_start_time_us,
								  const tas_target_client_info_st** target_client_info, uint32_t* num_client);

	const uint32_t* get_pkt_rq_session_start(tas_client_type_et client_type, const char* identifier, const char* session_id, 
											 const char* session_pw, tas_chl_target_et chl_target, uint64_t chl_param);
	tas_return_et   set_pkt_rsp_session_start(tas_client_type_et client_type, const uint32_t* pkt_rsp);

	const uint32_t* get_pkt_rq_device_unlock_get_challenge(tas_dev_unlock_cr_option_et ulcro);
	tas_return_et   set_pkt_rsp_device_unlock_get_challenge(const uint32_t* pkt_rsp, const void** challenge, uint16_t* challenge_length);

	const uint32_t* get_pkt_rq_device_unlock_set_key(tas_dev_unlock_option_et ulo, const void* key, uint16_t key_length);
	tas_return_et   set_pkt_rsp_device_unlock_set_key(const uint32_t* pkt_rsp);

	const uint32_t* get_pkt_rq_device_connect(tas_clnt_dco_et option);
	tas_return_et   set_pkt_rsp_device_connect(const uint32_t* pkt_rsp, uint16_t* dev_con_feat_used, uint32_t* device_type);

	const uint32_t* get_pkt_rq_device_reset_count();
	tas_return_et   set_pkt_rsp_device_reset_count(const uint32_t* pkt_rsp, tas_reset_count_st* reset_count);

private:

	enum {
		MAX_PKT_RQ_SIZE  = 1024,
		MAX_PKT_RSP_SIZE = 1024,
	};

	void mEnforceDerivedClass() { ; }

	tas_return_et mSetPktRspErrServerConnectionSetup();
	tas_return_et mSetPktRspErrServerLocked();
	tas_return_et mSetPktRspErrDeviceAccess();
	tas_return_et mSetPktRspErrDeviceLocked();

	tas_server_info_st mServerInfo;
	uint64_t mServerChallenge;

	enum { NUM_TARGET_MAX = 64 };
	tas_target_info_st mTargetInfo[NUM_TARGET_MAX];
	uint32_t mNumTarget;

	char mSessionName[TAS_NAME_LEN16];
	uint64_t mSessionStartTimeUs;

	enum { NUM_TARGET_CLIENT_MAX = 32 };
	tas_target_client_info_st mTargetClientInfo[NUM_TARGET_CLIENT_MAX];
	uint32_t mNumTargetClient;

	uint8_t mStartIndex;
};