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

#include "tas_socket.h"

class CTasConnSocket : public CTasSocket
{
public:
	bool connect(const char* hostname, unsigned short port);
	bool connect(const char* hostname, unsigned short port, unsigned int timeout_ms);

	int send(const void* buf, int len, int timeout_ms = -1);
	int sendAll(const void* buf, int len, int timeout_ms = -1);

	int recv(void* buf, int len, int timeout_ms = -1);
	int recvAll(void* buf, int len, int timeout_ms = -1);

	const char* get_remote_ip();

	unsigned short get_remote_port();

private:

	bool mConnectNonblock(const struct sockaddr* saptr, int salen, unsigned int timeout_ms);

	void mSleepMs(int timeout_ms);

	char mRemoteIp[INET6_ADDRSTRLEN] = "";

	std::chrono::milliseconds mLastTick = std::chrono::milliseconds(0);

protected:
	CTasConnSocket(int type, int protocol);
	CTasConnSocket(int conn_sock_desc);
};
