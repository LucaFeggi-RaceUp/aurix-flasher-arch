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

#include "tas_pkt.h"
#include "tas_client.h"

#include <chrono>
#include <thread>
#include <cstdint>
#include <assert.h>
#include <cstring>

#if defined(_WIN32)
#include <stdio.h>
#endif
#if linux
#include <stdio.h>
#endif

inline uint64_t tasutil_time_high_resolution_clock_us() 
{
	using namespace std::chrono;
	return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

inline uint64_t tasutil_time_ms()
{
	return tasutil_time_high_resolution_clock_us() / 1000;
}

inline time_t tasutil_time_since_epoch()
{
	using namespace std::chrono;
	return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

inline void tasutil_sleep_ms(long long x) 
{
	std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

inline bool tasutil_dev_con_phys_is_acc_hw(uint8_t dev_con_phys)
{
	switch (dev_con_phys) {
	case TAS_DEV_CON_PHYS_JTAG:
	case TAS_DEV_CON_PHYS_DAP:
	case TAS_DEV_CON_PHYS_DAP_DAP:
	case TAS_DEV_CON_PHYS_DAP_DXCPL:
	case TAS_DEV_CON_PHYS_DAP_DXCM:
	case TAS_DEV_CON_PHYS_SWD:
		return true;
	case TAS_DEV_CON_PHYS_ETH:
		return false;
	default: assert(false);
	}
	return false;
}

inline bool tasutil_dev_con_phys_supports_jtag_scans(uint8_t dev_con_phys)
{
	switch (dev_con_phys) {
	case TAS_DEV_CON_PHYS_JTAG:
	case TAS_DEV_CON_PHYS_DAP:
	case TAS_DEV_CON_PHYS_DAP_DAP:
	case TAS_DEV_CON_PHYS_DAP_DXCPL:
		return true;
	case TAS_DEV_CON_PHYS_DAP_DXCM:
	case TAS_DEV_CON_PHYS_SWD:
	case TAS_DEV_CON_PHYS_ETH:
		return false;
	default: assert(false);
	}
	return false;
}

enum { TASUTIL_TIME_STR_BUF_SIZE = 20 };
inline void tasutil_get_time_str(time_t time, char* str_buf)
{
#ifdef _MSC_VER
	struct tm timeTm;
	localtime_s(&timeTm, &time);
	strftime(str_buf, 20, "%Y-%m-%d %H:%M:%S", &timeTm);
#else
	struct tm* timeTm;
	timeTm = localtime(&time);
	strftime(str_buf, 20, "%Y-%m-%d %H:%M:%S", timeTm);
#endif
	assert(strlen(str_buf) < TASUTIL_TIME_STR_BUF_SIZE);
}

inline const char* tasutil_get_client_type_str(uint8_t client_type)
{
	switch (client_type) {
	case TAS_CLIENT_TYPE_RW:  return "ClientRw";
	case TAS_CLIENT_TYPE_CHL: return "ClientChl";
	case TAS_CLIENT_TYPE_TRC: return "ClientTrc";
	default: assert(false); return "UNKNOWN";
	}
}

inline const char* tasutil_get_dev_con_phys_str(uint8_t dev_con_phys)
{
	switch (dev_con_phys) {
	case TAS_DEV_CON_PHYS_UNKNOWN:   return "UNKNOWN";
	case TAS_DEV_CON_PHYS_JTAG:      return "JTAG";
	case TAS_DEV_CON_PHYS_DAP:       return "DAPx";
	case TAS_DEV_CON_PHYS_DAP_DAP:   return "DAP";
	case TAS_DEV_CON_PHYS_DAP_DXCPL: return "DXCPL";
	case TAS_DEV_CON_PHYS_DAP_DXCM:  return "DXCM";
	case TAS_DEV_CON_PHYS_SWD:       return "SWD";
	case TAS_DEV_CON_PHYS_ETH:       return "ETH";
	default: assert(false);          return "UNKNOWN";
	}
}

enum { TASUTIL_DEV_CON_FEAT_STR_BUF_SIZE = 128 };
void tasutil_get_dev_con_feat_str(uint16_t dev_con_feat, char* str_buf);

enum { TASUTIL_CON_INFO_STR_BUF_SIZE = 1024 };
int tasutil_get_con_info_str(const tas_con_info_st* con_info, char* str_buf, bool is_client_chl = false);
// Returns strlen() of str_buf

enum { TASUTIL_SERVER_INFO_STR_BUF_SIZE = 256 };
int tasutil_get_server_info_str(const char* ip_addr, uint16_t port_num, const tas_server_info_st* si, char* str_buf);
// Returns strlen() of str_buf

int tasutil_get_target_clients_str(
	const char* session_name, uint64_t session_start_time_us,
	const tas_target_client_info_st* tci, uint32_t num_client, 
	char* str_buf, int str_buf_size);
// Returns strlen() of str_buf

inline bool tasutil_dev_con_phys_is_dap_variant(tas_dev_con_phys_et dev_con_phys)
{
	switch (dev_con_phys) {
	case TAS_DEV_CON_PHYS_DAP:
	case TAS_DEV_CON_PHYS_DAP_DAP:
	case TAS_DEV_CON_PHYS_DAP_DXCPL:
	case TAS_DEV_CON_PHYS_DAP_DXCM:
		return true;
	}
	return false;
}

inline tas_return_et tasutil_assert(tas_return_et ret)
{
	if (ret != TAS_ERR_NONE)
		assert(ret == TAS_ERR_NONE);  // Set breakpoint here
	return ret;
}

inline uint32_t tasutil_crc32(const uint32_t* data32, uint32_t n_bytes)
{
	// Ethernet CRC. In case of mismatch consider
	// 1. Binary inversion
	// 2. MSB first vs LSB first 

	static const uint32_t crcTable[] =
	{
	  0x4DBDF21C, 0x500AE278, 0x76D3D2D4, 0x6B64C2B0,
	  0x3B61B38C, 0x26D6A3E8, 0x000F9344, 0x1DB88320,
	  0xA005713C, 0xBDB26158, 0x9B6B51F4, 0x86DC4190,
	  0xD6D930AC, 0xCB6E20C8, 0xEDB71064, 0xF0000000
	};

	const uint8_t* data8 = (const uint8_t*)data32;
	uint32_t n, crc = 0;
	for (n = 0; n < n_bytes; n++)
	{
		crc = (crc >> 4) ^ crcTable[(crc ^ (data8[n] >> 0)) & 0x0F];
		crc = (crc >> 4) ^ crcTable[(crc ^ (data8[n] >> 4)) & 0x0F];
	}
	return crc;
}

enum { TASUTIL_HASH32_STRBUF_SIZE = 8 };  // 6 + zero char would suffice
void tasutil_hash32_to_str(uint32_t hash32, char* hash32_str);
// Creates a string out of capital letters and numbers
// The string starts with a letter and has 6 characters
// The 3 MSB of the 32 bit hash are not used for the string generation

inline bool tasutil_check_if_tcpip_identifier(const char* identifier)
{
	assert(strlen(identifier) < TAS_NAME_LEN64);
	int nItems, a, b, c, d;

#ifdef _MSC_VER
	nItems = sscanf_s(identifier, "%d.%d.%d.%d", &a, &b, &c, &d);
#else
	nItems = sscanf(identifier, "%d.%d.%d.%d", &a, &b, &c, &d);
#endif
	return (nItems == 4);
}

inline int tasutil_sscanf_u64(const char* str, const char* format, uint64_t* value)
{
#ifdef _MSC_VER
	int nItems = sscanf_s(str, format, value);
#else
	int nItems = sscanf(str, format, value);
#endif
	if (nItems != 1)
		*value = 0;
	return nItems;
}

inline int tasutil_sscanf_u32(const char* str, const char* format, uint32_t* value)
{
#ifdef _MSC_VER
	int nItems = sscanf_s(str, format, value);
#else
	int nItems = sscanf(str, format, value);
#endif
	if (nItems != 1)
		*value = 0;
	return nItems;
}

void tasutil_get_user_name(char* user_name);
// Allocate TAS_NAME_LEN16 for user_name

uint32_t tasutil_get_pid();
// Get process ID

bool tasutil_check_local_tas_server_is_running();
void tasutil_start_local_tas_server();
// Convenience functions for Windows only

class CTasutilDeviceFrequ
{
public:

	CTasutilDeviceFrequ();

	void add_timer_sample(uint32_t timer_value, uint64_t timestamp_before_us, uint64_t timestamp_after_us);

	void get_timer_frequency(double* frequency_hz, double* max_deviation_hz);

	void clear() {
		mClearRefValue();
		mClearValue();
	}

private:

	void mClearRefValue();
	void mClearValue();

	uint32_t mRefTimerValue, mTimerValue;
	uint64_t mRefTimestampBeforeUs, mRefTimestampAfterUs;
	uint64_t mTimestampBeforeUs, mTimestampAfterUs;

};
