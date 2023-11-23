// TesteLocal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SwitchRequester.h"
#include "SwitchRequestResponder.h"

int main()
{
    DumbRequests dumb_requests;
    SwitchRequestResponder switch_request_responder(dumb_requests);
    SwitchRequester switch_requester(switch_request_responder);

    switch_requester.RequestBasicRequest();
}
