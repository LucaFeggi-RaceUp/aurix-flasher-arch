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
#include "tas_client_trc.h"

#include <assert.h>

CTasClientTrc::CTasClientTrc()
{
	assert(mMbIf);
}

CTasClientTrc::CTasClientTrc(CTasPktMailboxIf* mb_if)
{
	mMbIf = mb_if;
}

tas_return_et CTasClientTrc::subscribe(tas_trc_type_et* trct, uint8_t stream, tas_chso_et chso)
{
	const uint32_t *pktRq, *pktRsp;
	pktRq = mTphTrc->get_pkt_rq_subscribe(stream, chso);

	if (!mMbIf->execute(pktRq, (uint32_t*)&pktRsp))
		return tas_client_handle_error_server_con(&mEi);

	tas_chso_et chsoRsp;
	if (mTphTrc->set_pkt_rsp_subscribe(pktRsp, trct, &chsoRsp))
		return mEi.tas_err;

	return tas_clear_error_info(&mEi);
}

tas_return_et CTasClientTrc::unsubscribe(uint8_t stream)
{
	const uint32_t *pktRq, *pktRsp;
	pktRq = mTphTrc->get_pkt_rq_unsubscribe(stream);

	if (!mMbIf->execute(pktRq, (uint32_t*)&pktRsp))
		return tas_client_handle_error_server_con(&mEi);

	if (!mTphTrc->set_pkt_rsp_unsubscribe(pktRsp))
		return mEi.tas_err;

	return tas_clear_error_info(&mEi);
}

tas_return_et CTasClientTrc::rcv_trace(uint32_t timeout_ms, const void** trace_data, uint32_t* length, tas_trcs_et* trcs, uint8_t* stream)

{
	*trace_data = nullptr;
	*length = 0;
	*trcs = TAS_TRCS_CONT;
	if (stream)
		*stream = 0xFF;

	mMbIf->config(timeout_ms, TAS_PL2_MAX_PKT_SIZE);

	uint32_t* pktRsp = nullptr; assert(false);  // Need to implement this
	uint32_t rspNumBytesReceived;
	if (!mMbIf->receive(pktRsp, &rspNumBytesReceived))
		return tas_client_handle_error_server_con(&mEi);

	if (rspNumBytesReceived == 0) {
		tas_clear_error_info(&mEi);
		return TAS_ERR_CHL_RCV;  // Not TAS_ERR_NONE
	}

	const void* traceData; uint32_t lengthRcv; tas_trcs_et trcsRcv; uint8_t streamRcv;
	if (mTphTrc->set_pkt_rcv_trace(pktRsp, &traceData, &lengthRcv, &trcsRcv, &streamRcv))
		return mEi.tas_err;

	*trace_data = traceData;
	*length = lengthRcv;
	*trcs = trcsRcv;
	if (stream)
		*stream = streamRcv;

	return tas_clear_error_info(&mEi);
}

