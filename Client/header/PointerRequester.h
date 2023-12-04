#pragma once
#include "CommonStructures.h"
#include "ClientConnection.h"

class PointerRequester
{
public:
	PointerRequester(RequestPointers request_pointers, ClientConnection& client_connection);
	void RequestBasicRequestA();
	void RequestBasicRequestB();
	void RequestBasicRequestC();

private:
	RequestPointers Request_Pointers;
	ClientConnection& Client_Connection;
};