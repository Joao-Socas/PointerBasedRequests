#include "SwitchRequester.h"


SwitchRequester::SwitchRequester(const SwitchRequestResponder& switch_request_responder) : Switch_Request_Responder(switch_request_responder)
{
}

void SwitchRequester::RequestBasicRequest()
{
    SwitchRequest switch_request
    {
        .Request_Code = REQUEST_CODES::BASIC
    };
    Switch_Request_Responder.Request(switch_request);
}

DataExample SwitchRequester::RequestDataReceiveRequest()
{
    SwitchRequest switch_request
    {
        .Request_Code = REQUEST_CODES::DATA_RECEIVE
    };
    return Switch_Request_Responder.Request(switch_request);
}