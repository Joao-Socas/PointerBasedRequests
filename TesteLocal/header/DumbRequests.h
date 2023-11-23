#pragma once
#include <cstdint>
#include <CommonStructures.h>

class DumbRequests
{
public:
	void BasicRequest() const;
	DataExample DataReceiveRequest() const;
	void DataTransmitRequest(DataExample transmited_data) const;
	DataExample DataTranscieveRequest(DataExample transmited_data) const;
	
	RequestPointers This_Pointers = { 
		.Basic_Request_Pointer = std::bind(&DumbRequests::BasicRequest, this),
		.Data_Receive_Request_Pointer = std::bind(&DumbRequests::DataReceiveRequest, this),
		.Data_Transmit_Request_Pointer = std::bind(&DumbRequests::DataTransmitRequest, this, std::placeholders::_1),
		.Data_Transceive_Request_Pointer = std::bind(&DumbRequests::DataTranscieveRequest, this, std::placeholders::_1)
	};

	mutable uint32_t Basic_Called_Counter = 0;
	mutable uint32_t Data_Receive_Called_Counter = 0;
	mutable uint32_t Data_Trasmit_Called_Counter = 0;
	mutable uint32_t Data_Transcieve_Called_Counter = 0;
};