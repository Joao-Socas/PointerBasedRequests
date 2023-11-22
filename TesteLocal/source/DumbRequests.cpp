#include "DumbRequests.h"

void DumbRequests::BasicRequest() const
{
    Basic_Called_Counter++;
}

DataExample DumbRequests::DataReceiveRequest() const
{
    Data_Receive_Called_Counter++;
}

void DumbRequests::DataTransmitRequest(DataExample trasnmited) const
{
    Data_Trasmit_Called_Counter++;
}

DataExample DumbRequests::DataTranscieveRequest(DataExample trasnmited) const
{
    Data_Transcieve_Called_Counter++;
}
