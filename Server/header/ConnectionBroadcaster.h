#pragma once
// STD Includes
#include <cstdint>

// Boost Includes
#include "boost/asio.hpp"
#include "boost/asio/ip/host_name.hpp"

// Common Includes
#include "CommonStructures.h"

class ConnectionBroadcaster
{
public:
	ConnectionBroadcaster(uint32_t port);
	void StartBroadcastIP();
	void StopBroadcastIP();

	bool Is_Broadcasting = false;
private:
	void BroadcastIP();

	boost::asio::io_context Server_Broadcast_Context;
	boost::asio::ip::tcp::resolver Self_Resolver = boost::asio::ip::tcp::resolver(Server_Broadcast_Context);
	std::unique_ptr<boost::asio::ip::udp::endpoint> Broadcast_Endpoint;
	std::unique_ptr<boost::asio::ip::udp::socket> Broadcast_Socket;

	std::unique_ptr<std::thread> Broadcast_Thread;
	std::vector<BroadcastData> Broadcast_Data_Array;
	char Broadcast_Buffer[sizeof(BroadcastData)] = "\0";
	
	// Class inputs
	uint32_t Port;

	bool Should_Broadcast = false;
};