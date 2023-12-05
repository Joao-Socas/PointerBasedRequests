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
		RequestRoutines::Routine_A();
		break;
	case REQUEST_CODES::BASIC_B:
		RequestRoutines::Routine_B();
		break;
	case REQUEST_CODES::BASIC_C:
		RequestRoutines::Routine_C();
		break;
	case REQUEST_CODES::BASIC_D:
		RequestRoutines::Routine_D();
		break;
	case REQUEST_CODES::BASIC_E:
		RequestRoutines::Routine_E();
		break;
	case REQUEST_CODES::BASIC_F:
		RequestRoutines::Routine_F();
		break;
	case REQUEST_CODES::BASIC_G:
		RequestRoutines::Routine_G();
		break;
	case REQUEST_CODES::BASIC_H:
		RequestRoutines::Routine_H();
		break;
	case REQUEST_CODES::BASIC_I:
		RequestRoutines::Routine_I();
		break;
	case REQUEST_CODES::BASIC_J:
		RequestRoutines::Routine_J();
		break;
	case REQUEST_CODES::BASIC_K:
		RequestRoutines::Routine_K();
		break;
	case REQUEST_CODES::BASIC_L:
		RequestRoutines::Routine_L();
		break;
	case REQUEST_CODES::BASIC_M:
		RequestRoutines::Routine_M();
		break;
	case REQUEST_CODES::BASIC_N:
		RequestRoutines::Routine_N();
		break;
	case REQUEST_CODES::BASIC_O:
		RequestRoutines::Routine_O();
		break;
	case REQUEST_CODES::BASIC_P:
		RequestRoutines::Routine_P();
		break;
	case REQUEST_CODES::BASIC_Q:
		RequestRoutines::Routine_Q();
		break;
	case REQUEST_CODES::BASIC_R:
		RequestRoutines::Routine_R();
		break;
	case REQUEST_CODES::BASIC_S:
		RequestRoutines::Routine_S();
		break;
	case REQUEST_CODES::BASIC_T:
		RequestRoutines::Routine_T();
		break;
	case REQUEST_CODES::BASIC_U:
		RequestRoutines::Routine_U();
		break;
	case REQUEST_CODES::BASIC_V:
		RequestRoutines::Routine_V();
		break;
	case REQUEST_CODES::BASIC_W:
		RequestRoutines::Routine_W();
		break;
	case REQUEST_CODES::BASIC_X:
		RequestRoutines::Routine_X();
		break;
	case REQUEST_CODES::BASIC_Y:
		RequestRoutines::Routine_Y();
		break;
	case REQUEST_CODES::BASIC_Z:
		RequestRoutines::Routine_Z();
		break;
	default:
		// Bad request
		break;
	}
}
