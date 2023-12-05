#include "SwitchRequester.h"
#include <random>
#include <cstdint>

SwitchRequester::SwitchRequester(ClientConnection& client_connection) : Client_Connection(client_connection)
{
}

//void SwitchRequester::RequestBasicRequestA()
//{
//    REQUEST_CODES request = REQUEST_CODES::BASIC_A;
//    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(&request), sizeof(request));
//}
//
//void SwitchRequester::RequestBasicRequestB()
//{
//    REQUEST_CODES request = REQUEST_CODES::BASIC_B;
//    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(&request), sizeof(request));
//}
//
//void SwitchRequester::RequestBasicRequestC()
//{
//    REQUEST_CODES request = REQUEST_CODES::BASIC_C;
//    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(&request), sizeof(request));
//}
void SwitchRequester::MultipleRequestTest()
{
    MultipleSwitchRequestsTest* multiple_requests = new MultipleSwitchRequestsTest();
    std::random_device random_device;
    std::mt19937 random_generator(random_device());
    std::uniform_int_distribution<> uniform_distributor(1, 3);
    for (uint32_t i = 0; i < 100000; i++)
    {
        int32_t randon_number = uniform_distributor(random_generator);
        switch (randon_number)
        {
        case 1:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_A;
            break;
        case 2:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_B;
            break;
        case 3:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_C;
            break;
        case 4:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_D;
            break;
        case 5:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_E;
            break;
        case 6:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_F;
            break;
        case 7:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_G;
            break;
        case 8:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_H;
            break;
        case 9:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_I;
            break;
        case 10:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_J;
            break;
        case 11:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_K;
            break;
        case 12:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_L;
            break;
        case 13:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_M;
            break;
        case 14:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_N;
            break;
        case 15:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_O;
            break;
        case 16:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_P;
            break;
        case 17:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_Q;
            break;
        case 18:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_R;
            break;
        case 19:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_S;
            break;
        case 20:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_T;
            break;
        case 21:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_U;
            break;
        case 22:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_V;
            break;
        case 23:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_W;
            break;
        case 24:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_X;
            break;
        case 25:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_Y;
            break;
        case 26:
            multiple_requests->Request_Codes[i] = REQUEST_CODES::BASIC_Z;
            break;
        default:
            break;
        }
    }

    Client_Connection.SwitchRequestSend(reinterpret_cast<char*>(multiple_requests), sizeof(MultipleSwitchRequestsTest));
    delete multiple_requests;
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