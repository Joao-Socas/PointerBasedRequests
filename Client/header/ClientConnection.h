#pragma once

// STD Includes
#include <vector>
#include <functional>
#include <thread>

// Boost Includes
#include "boost/asio.hpp"
// Common Includes
#include "CommonStructures.h"
// Project Includes
#include "BroadcastListener.h"


class ClientConnection
{
public:
	ClientConnection();
	~ClientConnection();

	void Connect(BroadcastData broadcast_data);
	void PointerRequestSend(char* buffer, std::size_t buffer_size);
	void SwitchRequestSend(char* buffer, std::size_t buffer_size);

private:
	bool TimeoutConnect(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint& endpoint);
	bool TimeoutRead(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, char* buffer, std::size_t buffer_size);
	void KeepServerConnectionAlive();
		
	BroadcastListener Broadcast_Listener;

	boost::asio::io_context Connection_Context;

	std::unique_ptr<boost::asio::ip::tcp::socket> Pointer_Request_Socket;
	std::unique_ptr<boost::asio::ip::tcp::socket> Switch_Request_Socket;
	boost::asio::io_context Request_Context;
	std::unique_ptr<boost::asio::ip::tcp::endpoint> Server_Endpoint;
	std::unique_ptr<boost::asio::ip::tcp::socket> Server_Socket;
	std::unique_ptr<std::thread> Keep_Server_Connection_Alive_Thread;

	bool Connected = false;
	bool Exiting = false;
	ClientConnectionParams ConnectionParams = {};

};

