#pragma once

// STD Includes
#include <vector>
#include <functional>
#include <thread>

// Boost Includes
#include "boost/asio.hpp"
// Project Includes
#include "CommonStructures.h"

class ClientConnection
{
public:
	ClientConnection(std::function<void()>& cancel_connection);
	~ClientConnection();

	void Connect(BroadcastData broadcast_data);

private:

	void HearBroadcast();
	void StopHearingBroadcast();
	void ShowBroadcastPoll();
	bool GetBroadcastSellection(BroadcastData& target_server);
	void ChooseServer(BroadcastData& target_server);
	void StartConnection(BroadcastData& target_server);
	bool TimeoutConnect(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint& endpoint);
		
	boost::asio::io_context Server_IO_Context; // This is reserved for all server operations, including broadcast hearing
	boost::asio::ip::tcp::resolver Self_Resolver = boost::asio::ip::tcp::resolver(Server_IO_Context);
	std::unique_ptr<boost::asio::ip::udp::socket> Broadcast_Socket;
	std::unique_ptr<boost::asio::ip::udp::endpoint> Client_Broadcast_Endpoint;
	bool Should_Hear_Broadcast;
	boost::asio::io_context Broadcast_IO_Context; // This one is only for the broadcast hearing thread
	std::unique_ptr<std::thread> Broadcast_Thread; 
	void HearBroadcastThread();
	void BroadcastError(std::string broadcast_error);
	std::vector<BroadcastData> Broadcast_Poll;

	void KeepServerConnectionAlive();
	bool TimeoutRead(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, char* buffer, std::size_t buffer_size);
	std::unique_ptr<boost::asio::ip::tcp::endpoint> Server_Endpoint;
	std::unique_ptr<boost::asio::ip::tcp::socket> Server_Socket;
	std::unique_ptr<std::thread> Keep_Server_Connection_Alive_Thread;

	std::function<void()>& Cancel_Connection;

	bool Connected = false;
	bool Exiting = false;
	ClientConnectionParams ConnectionParams;

};