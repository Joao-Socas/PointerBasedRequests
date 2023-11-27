#include "PointerRequester.h"

PointerRequester::PointerRequester(RequestPointers request_pointers, ClientConnection& client_connection) : 
    Request_Pointers(request_pointers), Client_Connection(client_connection)
{
}

void PointerRequester::RequestBasicRequest()
{
    Pointer_Request_Responder.Request(PointerRequest{.Request_Pointer = Request_Pointers.Basic_Request_Pointer})
}
