#include "PointerRequester.h"
#include <random>
#include <cstdint>

PointerRequester::PointerRequester(RequestPointers request_pointers, ClientConnection& client_connection) : 
    Request_Pointers(request_pointers), Client_Connection(client_connection)
{
}

//void PointerRequester::RequestBasicRequestA()
//{
//    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(Request_Pointers.Basic_Request_Pointer_A), sizeof(Request_Pointers.Basic_Request_Pointer_A));
//}
//
//void PointerRequester::RequestBasicRequestB()
//{
//    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(Request_Pointers.Basic_Request_Pointer_B), sizeof(Request_Pointers.Basic_Request_Pointer_B));
//}
//
//void PointerRequester::RequestBasicRequestC()
//{
//    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(Request_Pointers.Basic_Request_Pointer_C), sizeof(Request_Pointers.Basic_Request_Pointer_C));
//}

void PointerRequester::MultipleRequestTest()
{
    MultiplePointerRequestsTest* multiple_requests = new MultiplePointerRequestsTest();
    std::random_device random_device;
    std::mt19937 random_generator(random_device());
    std::uniform_int_distribution<> uniform_distributor(1, 26);
    for (uint32_t i = 0; i < 100000; i++)
    {
        int32_t randon_number = uniform_distributor(random_generator);
        switch (randon_number)
        {
        case 1:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_A;
            break;
        case 2:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_B;
            break;
        case 3:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_C;
            break;
        case 4:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_D;
            break;
        case 5:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_E;
            break;
        case 6:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_F;
            break;
        case 7:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_G;
            break;
        case 8:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_H;
            break;
        case 9:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_I;
            break;
        case 10:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_J;
            break;
        case 11:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_K;
            break;
        case 12:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_L;
            break;
        case 13:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_M;
            break;
        case 14:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_N;
            break;
        case 15:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_O;
            break;
        case 16:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_P;
            break;
        case 17:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_Q;
            break;
        case 18:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_R;
            break;
        case 19:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_S;
            break;
        case 20:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_T;
            break;
        case 21:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_U;
            break;
        case 22:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_V;
            break;
        case 23:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_W;
            break;
        case 24:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_X;
            break;
        case 25:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_Y;
            break;
        case 26:
            multiple_requests->Request_Pointers[i] = Request_Pointers.Basic_Request_Pointer_Z;
            break;
        default:
            break;
        }
    }

    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(multiple_requests), sizeof(MultiplePointerRequestsTest));
    delete multiple_requests;
}
