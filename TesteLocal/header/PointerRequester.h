#pragma once
#include "CommonStructures.h"
#include "DumbRequests.h"
#include "PointerRequestResponder.h"

class PointerRequester
{
public:
	PointerRequester(RequestPointers request_pointers, PointerRequesterResponder& pointer_request_responder);
	void RequestBasicRequest();

private:
	RequestPointers Request_Pointers;
	PointerRequesterResponder& Pointer_Request_Responder;
};