#include "SwitchRequestResponder.h"

SwitchRequestResponder::SwitchRequestResponder(const DumbRequests& dumb_requests) : Dumb_Requests(dumb_requests)
{
}

DataExample SwitchRequestResponder::Request(SwitchRequest request) const
{
	switch (request.Request_Code)
	{
	case REQUEST_CODES::BASIC:
		Dumb_Requests.BasicRequest();
		break;
	case REQUEST_CODES::DATA_RECEIVE:
		return Dumb_Requests.DataReceiveRequest();
		break;
	case REQUEST_CODES::DATA_TRANSMIT:
		Dumb_Requests.DataTransmitRequest(request.Data_Example);
		break;
	case REQUEST_CODES::DATA_TRANSCEIVE:
		return Dumb_Requests.DataTranscieveRequest(request.Data_Example);
		break;
	}
	return DataExample{};
}
