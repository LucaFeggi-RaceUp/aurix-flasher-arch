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

#if defined(_WIN32) || defined(_WIN64)
	#include <WinSock2.h>
	#include <ws2tcpip.h>
	#pragma comment (lib, "Ws2_32.lib")
#else
	#include <sys/types.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#define INVALID_SOCKET  (int)(~0)
	#define SOCKET_ERROR -1
#endif

#include <cstring>
#include <chrono>
#include <thread>

// Call WSACleanUp() at the end of socket usage in win applications

class CTasSocket
{
public:
	CTasSocket(const CTasSocket&) = delete; // delete the copy constructor
	CTasSocket operator= (const CTasSocket&) = delete; // delete copy-assignment operator
	~CTasSocket(); // closes the socket

	int select_socket(const unsigned int msec);
	bool set_option(int optname, void* arg);

	bool set_local_port(unsigned short port);
	unsigned short get_local_port();

	//void set_local_addr(const char* addr);
	const char* get_local_addr();

	bool set_local_addr_and_port(const char* addr, unsigned short port);
	//void get_local_addr_and_port();

	void close();

private:
	char mLocalIpv4[INET_ADDRSTRLEN] = "";

protected:
	int mSocketDesc; // socket descriptor
	CTasSocket(int type, int protocol); // socket constructor with its type and protocol 
	CTasSocket(int socket_desc);
};