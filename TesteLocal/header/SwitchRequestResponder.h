#pragma once
#include "CommonStructures.h"
#include "DumbRequests.h"

class SwitchRequestResponder
{
public:
	SwitchRequestResponder(const DumbRequests& dumb_request);
	void Request(SwitchRequest request);

private:
	const DumbRequests& Dumb_Requests;
};