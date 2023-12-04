#include "PointerRequester.h"

PointerRequester::PointerRequester(RequestPointers request_pointers, ClientConnection& client_connection) : 
    Request_Pointers(request_pointers), Client_Connection(client_connection)
{
}

void PointerRequester::RequestBasicRequestA()
{
    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(Request_Pointers.Basic_Request_Pointer_A), sizeof(Request_Pointers.Basic_Request_Pointer_A));
}

void PointerRequester::RequestBasicRequestB()
{
    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(Request_Pointers.Basic_Request_Pointer_B), sizeof(Request_Pointers.Basic_Request_Pointer_B));
}

void PointerRequester::RequestBasicRequestC()
{
    Client_Connection.PointerRequestSend(reinterpret_cast<char*>(Request_Pointers.Basic_Request_Pointer_C), sizeof(Request_Pointers.Basic_Request_Pointer_C));
}