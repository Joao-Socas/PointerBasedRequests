#include "DumbRequests.h"

void DumbRequests::BasicRequest() const
{
    Basic_Called_Counter++;
}

DataExample DumbRequests::DataReceiveRequest() const
{
    Data_Receive_Called_Counter++;
    return DataExample{ .Data_Content{"This is example return data."} };
}

void DumbRequests::DataTransmitRequest(DataExample transmited_data) const
{
    Data_Trasmit_Called_Counter++;
}

DataExample DumbRequests::DataTranscieveRequest(DataExample transmited_data) const
{
    Data_Transcieve_Called_Counter++;
    strcpy_s(transmited_data.Data_Content, "This example data was altered.");
    return transmited_data;
}
