#pragma once
#include "CommonStructures.h"
#include "DumbRequests.h"

class SwitchRequestResponder
{
public:
	SwitchRequestResponder(const DumbRequests& dumb_request);
	DataExample Request(SwitchRequest request) const;

private:
	const DumbRequests& Dumb_Requests;
};