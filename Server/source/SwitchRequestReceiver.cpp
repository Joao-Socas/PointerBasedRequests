#include "SwitchRequestReceiver.h"
#include "RequestRoutines.h"

SwitchRequestReceiver::SwitchRequestReceiver()
{
}

void SwitchRequestReceiver::ReceiveRequest(REQUEST_CODES request_code)
{
	switch (request_code)
	{
	case REQUEST_CODES::BASIC_A:
		// Timer stop
		RequestRoutines::Routine_A();
		break;
	case REQUEST_CODES::BASIC_B:
		// Timer stop
		RequestRoutines::Routine_B();
		break;
	case REQUEST_CODES::BASIC_C:
		// Timer stop
		RequestRoutines::Routine_C();
		break;
	default:
		// Bad request
		break;
	}
}
