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

#include "tas_pkt_mailbox_socket.h"
#include "tas_pkt_handler_server_con.h"


class CTasClientServerCon  // Common for CHL, RW and TRC clients
{

public:

	~CTasClientServerCon();

	const char* get_error_info() { return mEip->info; }
	
	tas_return_et server_connect(const char* ip_addr, uint16_t port_num = TAS_PORT_NUM_SERVER_DEFAULT);
	// In case of TAS_ERR_SERVER_LOCKED use server_unlock() and optional get_server_challenge() before

	const char* get_server_ip_addr() { return mServerIpAddr; }
	uint16_t get_server_port_num() { return mServerPortNum; }

	const tas_server_info_st* get_server_info() { return mServerInfo; }
	// Returns the server information from the last server_connect() call
	// nullptr if no server connected

	uint64_t get_server_challenge() { return mServerChallenge; }
	// Returns the server challenge from the last server_connect() call
	// Returns 0 if no challenge

	tas_return_et server_unlock(const void* key, uint16_t key_length);

	// XXXXX Server setup
	// Do we need a challenge type description? Or is it always a string? -> adapt get_server_challenge()
	// How to do the encryption - end to end?

	tas_return_et get_targets(const tas_target_info_st** target_info, uint32_t* num_target);
	// The target_info array lists all targets that are connected to the server
	// target_info.identifier contains the unique access HW name or the IP address of the device
	// Several clients (target_info.num_client) can be connected to one target

	tas_return_et get_target_clients(const char* identifier, const char** session_name, 
									 uint64_t* session_start_time_us,
		                             const tas_target_client_info_st** target_client_info, 
									 uint32_t* num_client);
	// The target_client_info array lists all clients that are connected to the target selected by identifier
	// Allows to get the session_name of a running session. Please note that a tool may not automatically
	// connect to a running session with a retrieved session name. Otherwise there is a high risk for 
	// unintended conflicts between different users.
	
	// tas_return_et session_start(const char* identifier, const char* session_name = "", const char* session_pw = "")
	// Start a session by establishing a target connection
	// A target can be a device or just an access HW without a device connected
	// session_name and session_pw protect from uncontrolled accesses by other clients
	// If no client is connected to a target, the first client sets session_name and session_pw 

	// Once a session was successfully started it is not allowed to call session_start() again
	// A session is ended by the destructor 


	const tas_con_info_st* get_con_info() { return mTphsc.get_con_info(); }

	tas_return_et device_unlock_get_challenge(tas_dev_unlock_cr_option_et ulcro, const void** challenge, uint16_t* challenge_length);
	// ulcro can select device specific challenge response sequence options

	tas_return_et device_unlock_set_key(tas_dev_unlock_option_et ulo, const void* key, uint16_t key_length);
	// Maximum key_length is 512 bytes (TAS_UNLOCK_MAX_KEY_LEN). If 0, the key in the TasServer is cleared.

	virtual tas_return_et device_connect(tas_clnt_dco_et dco) = 0;
	// Connect device with hot attach, reset or reset and halt
	// Will use the provided key for unlocking if needed

	virtual bool device_reset_occurred() = 0;
	// Returns true if at least one device reset occurred since the last call.
	// Prerequisite is that there was a device interaction in between.
	// For ClientRw this means an RW access and for ClientChl that a message was received.
	// device_connect() sets the reference point.
	// The reset information is collected from all device accesses by all clients before
	// Not all hardware setups will support this feature

protected:

	CTasClientServerCon(const char* client_name, tas_error_info_st* ei, CTasPktMailboxIf* mb_if = nullptr);
	// user_name is retrieved from the OS

	tas_return_et mSessionStart(tas_client_type_et client_type, 
		                        const char* identifier, const char* session_name, const char* session_pw,
								tas_chl_target_et chl_target = TAS_CHL_TGT_UNKNOWN, uint64_t chl_param = 0);

	tas_return_et mDeviceConnect(tas_clnt_dco_et dco);

	CTasPktMailboxIf* mMbIf = nullptr;

	CTasPktMailboxSocket* mMbSocket = nullptr;

	bool mSessionStarted = false;

	// For TAS_CHT_RCV and TAS_CHT_BIDI some client functions are not supported
	bool mRcvChlActive = false;

	uint32_t mDeviceResetCount = ~0;

private:

	tas_return_et mHandleErrorServerConnect(const char* ip_addr, uint16_t port_num);
	tas_return_et mHandleErrorRcvChlActive();

	char mClientName[TAS_NAME_LEN32];  // As in tas_pl1rq_server_connect_st;
	char mUserName[TAS_NAME_LEN16];
	uint32_t mClientPid;

	CTasPktHandlerServerCon mTphsc;

	tas_error_info_st* mEip;  // Pointer to single object in primary client class

	enum { IP_ADDR_NAME_BUF_SIZE = 256 };
	char 	 mServerIpAddr[IP_ADDR_NAME_BUF_SIZE];
	uint16_t mServerPortNum = 0;

	const tas_server_info_st* mServerInfo;
	uint64_t                  mServerChallenge;

};