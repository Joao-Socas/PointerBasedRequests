#include "SwitchRequester.h"


SwitchRequester::SwitchRequester(ClientConnection& client_connection) : Client_Connection(client_connection)
{
}

void SwitchRequester::RequestBasicRequestA()
{
    REQUEST_CODES request = REQUEST_CODES::BASIC_A;
    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(&request), sizeof(request));
}

void SwitchRequester::RequestBasicRequestB()
{
    REQUEST_CODES request = REQUEST_CODES::BASIC_B;
    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(&request), sizeof(request));
}

void SwitchRequester::RequestBasicRequestC()
{
    REQUEST_CODES request = REQUEST_CODES::BASIC_C;
    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(&request), sizeof(request));
}
//
//DataExample SwitchRequester::RequestDataReceiveRequest()
//{
//    SwitchRequest switch_request
//    {
//        .Request_Code = REQUEST_CODES::DATA_RECEIVE
//    };
//    return Switch_Request_Responder.Request(switch_request);
//}