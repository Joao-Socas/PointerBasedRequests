#pragma once
#include "CommonStructures.h"
#include "ClientConnection.h"

class PointerRequester
{
public:
	PointerRequester(RequestPointers request_pointers, ClientConnection& client_connection);
	void RequestBasicRequest();

private:
	RequestPointers Request_Pointers;
	ClientConnection& Client_Connection;
};