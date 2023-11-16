#pragma once
#include "CommonStructures.h"
#include "DumbRequests.h"

class PointerRequester
{
public:
	PointerRequester(const DumbRequests& dumb_requests, RequestPointers request_pointers);
	void RequestBasicRequest();

	~PointerRequester();

private:
	const DumbRequests& Dumb_Requests;
	RequestPointers Request_Pointers;
};