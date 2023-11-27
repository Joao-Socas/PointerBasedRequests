#pragma once
// STD Includes
#include <vector>
#include <memory>
#include <cstdint>

// Boost Includes
#include "boost/asio.hpp"

// Common Includes
#include "CommonStructures.h"

class BroadcastListener
{
public:
	BroadcastListener(uint32_t port);
	void ListenBroadcast();
	void StopListeningBroadcast();
	BroadcastData ChooseServer();
	bool Is_Listening_Broadcast = false;

private:
	// Class inputs
	uint32_t Port = NULL;

	void ListenBroadcastThread();
	void ShowBroadcastPoll();

	boost::asio::io_context Broadcast_Listen_Context; // This is reserved for all server operations, including broadcast hearing
	boost::asio::ip::tcp::resolver Self_Resolver = boost::asio::ip::tcp::resolver(Broadcast_Listen_Context);
	std::unique_ptr<boost::asio::ip::udp::socket> Broadcast_Socket;
	std::unique_ptr<boost::asio::ip::udp::endpoint> Client_Broadcast_Endpoint;
	bool Should_Listen_Broadcast = false;
	std::vector<BroadcastData> Broadcast_Poll;
	boost::asio::io_context Broadcast_Thread_Context; // This one is only for the broadcast hearing thread
	std::unique_ptr<std::thread> Broadcast_Thread;
};