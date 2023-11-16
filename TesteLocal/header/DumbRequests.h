#pragma once
#include <cstdint>

class DumbRequests
{
public:
	void BasicRequest();
	void DataReceiveRequest();
	void DataTransmitRequest();
	void DataTranscieveRequest();
	
	RequestPointers This_Pointers = { 
		.Basic_Request_Pointer = std::bind(&DumbRequests::BasicRequest, this),
		.Data_Receive_Request_Pointer = std::bind(&DumbRequests::DataReceiveRequest, this),
		.Data_Transmit_Request_Pointer = std::bind(&DumbRequests::DataTransmitRequest, this),
		.Data_Transceive_Request_Pointer = std::bind(&DumbRequests::DataTranscieveRequest, this)
	};
private:
	mutable uint32_t Basic_Called_Counter = 0;
	mutable uint32_t Data_Receive_Called_Counter = 0;
	mutable uint32_t Data_Trasmit_Called_Counter = 0;
	mutable uint32_t Data_Transcieve_Called_Counter = 0;
};