#include "SwitchRequestResponder.h"

SwitchRequestResponder::SwitchRequestResponder(const DumbRequests& dumb_requests) : Dumb_Requests(dumb_requests)
{
}

void SwitchRequestResponder::Request(SwitchRequest request)
{
	switch (request.Request_Code)
	{
	case REQUEST_CODES::BASIC:
		Dumb_Requests.BasicRequest();
		break;
	case REQUEST_CODES::DATA_RECEIVE:
		break;
	case REQUEST_CODES::DATA_TRANSMIT:
		break;
	case REQUEST_CODES::DATA_TRANSCEIVE:
		break;
	default:
		break;
	}
}
