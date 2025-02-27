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

#include "tas_pkt_mailbox_if.h"

#include "tas_tcp_socket.h"

class CTasPktMailboxSocket : public CTasPktMailboxIf
{

public:

	CTasPktMailboxSocket()
	{
		mSocket = nullptr;
		mMaxNumBytesRsp = 0;
		mRspBuf = nullptr;
		mNumBytesRsp = 0;
		mTimeoutReceiveMs = 0;
	}

	~CTasPktMailboxSocket()
	{
		mSocketDisconnect();
	}

	bool server_connect(const char* ip_addr, uint16_t port_num);

	// CTasPktMailboxIf
	void config(uint32_t timeout_receive_ms, uint32_t max_num_bytes_rsp);
	bool connected() { return (mSocket != nullptr); }
	bool send(const uint32_t* rq, uint32_t num_pl2_pkt = 1);
	bool receive(uint32_t* rsp, uint32_t* num_bytes_rsp);
	bool execute(const uint32_t* rq, uint32_t* rsp, uint32_t num_pl2_pkt = 1, uint32_t* num_bytes_rsp = nullptr);

private:

	bool mReceivePl2Pkt();

	bool mSocketSend(const uint32_t* rq, uint32_t num_bytes);
	bool mSocketReceive(uint32_t w, uint32_t num_bytes);  // w is index in mRspBuf[w]

	void mSocketDisconnect()  // In case of fatal errors
	{
		delete mSocket;
		mSocket = nullptr;
	}

	CTasTcpSocket* mSocket;

	uint32_t mTimeoutReceiveMs;

	uint32_t  mMaxNumBytesRsp;

	uint32_t* mRspBuf;
	uint32_t  mNumBytesRsp;
};