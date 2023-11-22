#pragma once
#include "DumbRequests.h"

class PointerRequesterResponder
{
public:
	PointerRequesterResponder(const DumbRequests& dumb_requests);
	void Request(PointerRequest pointer_request);

private:
	const DumbRequests& Dumb_Requests;
};