#include "DumbRequests.h"

void DumbRequests::BasicRequest()
{
    Basic_Called_Counter++;
}

void DumbRequests::DataReceiveRequest()
{
    Data_Receive_Called_Counter++;
}

void DumbRequests::DataTransmitRequest()
{
    Data_Trasmit_Called_Counter++;
}

void DumbRequests::DataTranscieveRequest()
{
    Data_Transcieve_Called_Counter++;
}
