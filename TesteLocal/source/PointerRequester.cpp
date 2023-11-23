#include "PointerRequester.h"
#include "PointerRequestResponder.h"

PointerRequester::PointerRequester(RequestPointers request_pointers, PointerRequesterResponder& pointer_request_responder) :
    Request_Pointers(request_pointers), 
    Pointer_Request_Responder(pointer_request_responder)
{
}

void PointerRequester::RequestBasicRequest()
{
    Pointer_Request_Responder.Request(PointerRequest{.Request_Pointer = Request_Pointers.Basic_Request_Pointer})
}
