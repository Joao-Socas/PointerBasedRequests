#pragma once
#include "CommonStructures.h"
#include "SwitchRequestResponder.h"

class SwitchRequester
{
public:
	SwitchRequester(const SwitchRequestResponder& switch_request_responder);

	void RequestBasicRequest();
	DataExample RequestDataReceiveRequest();
	void RequestDataTransmitRequest(DataExample);
	DataExample RequestDataTransceiveRequest(DataExample);

private:
	const SwitchRequestResponder& Switch_Request_Responder;
};