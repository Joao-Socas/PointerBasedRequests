#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include <cstdint>

#include "DumbRequests.h"
#include "SwitchRequester.h"
#include "SwitchRequestResponder.h"

constexpr uint32_t TEST_ITERATIONS = 1000;
BOOST_AUTO_TEST_CASE(SwitchBasicRequest)
{
    DumbRequests dumb_requests;
    SwitchRequestResponder switch_request_responder(dumb_requests);
    SwitchRequester switch_requester(switch_request_responder);

    for (int32_t i = 0; i < TEST_ITERATIONS; i++)
    {
        switch_requester.RequestBasicRequest();
    }

    BOOST_TEST(dumb_requests.Basic_Called_Counter == TEST_ITERATIONS);
};