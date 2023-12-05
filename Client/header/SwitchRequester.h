#pragma once
#include "CommonStructures.h"
#include "ClientConnection.h"

class SwitchRequester
{
public:
	SwitchRequester(ClientConnection& client_connection);

	void RequestBasicRequestA();
	void RequestBasicRequestB();
	void RequestBasicRequestC();

	void MultipleRequestTest();
	//DataExample RequestDataReceiveRequest();
	//void RequestDataTransmitRequest(DataExample);
	//DataExample RequestDataTransceiveRequest(DataExample);

private:
	ClientConnection& Client_Connection;
};