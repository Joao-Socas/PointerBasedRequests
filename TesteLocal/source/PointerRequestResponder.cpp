#include "PointerRequestResponder.h"

PointerRequesterResponder::PointerRequesterResponder(const DumbRequests& dumb_requests) : Dumb_Requests(dumb_requests)
{
}

void PointerRequesterResponder::Request(PointerRequest pointer_request)
{
    // In this example, we put pointer_request inside so if the function needs some data, it can find.
    // In the network example, we first just read the header, and then, if there is any required, the data from the socket
    pointer_request.Request_Pointer(pointer_request);
}