#pragma once
// STD Includes
#include <cstdint>
#include <memory>
#include <thread>
#include <functional>
// Boost Inlcudes
#include "boost/asio.hpp"
#include "boost/asio/ip/host_name.hpp"
// Common Includes
#include "CommonStructures.h"
// Project Includes
#include "Logger.h"
#include "ConnectionBroadcaster.h"

class ServerConnection
{
public:
    ServerConnection(std::function<void()>& cancel_connection);
	void StartConnection(); 
	void CancelConnection();

private:
	void ConnectionProposal();
	bool TimeoutRead(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, char* buffer, std::size_t buffer_size);

	void ConnectionProposalCheck(char* buffer);

	void ScoutConnection();
		
	ConnectionBroadcaster Connection_Broadcaster;
	boost::asio::io_context Connection_Context;
	boost::asio::io_context Connection_Loop_Context;
	boost::asio::io_context Request_Context;
	std::unique_ptr<boost::asio::ip::tcp::endpoint> Server_Endpoint;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> Acceptor;
	std::unique_ptr<boost::asio::ip::tcp::socket> Connection_Socket;
	std::unique_ptr<boost::asio::ip::tcp::socket> Pointer_Request_Socket;
	std::unique_ptr<boost::asio::ip::tcp::socket> Switch_Request_Socket;




	void WaitForConnection();
	uint32_t Sync_ID = 0; // this is for preventing async rotines to continue if a cancel/disconnect was requested from the UI

	bool Connected = false;
	bool KeepAlive = true;
	std::function<void()>& Cancel_Connection;
};