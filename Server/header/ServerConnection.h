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
#include "SwitchRequestReceiver.h"
#include "PointerRequestReceiver.h"

class ServerConnection
{
public:
    ServerConnection();
	void StartConnection(); 
	void CancelConnection();

private:
	void ConnectionProposal();
	bool TimeoutRead(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, char* buffer, std::size_t buffer_size);

	void ConnectionProposalCheck(char* buffer);

	void WaitForConnection();
	void ScoutConnection();
	void StartListeningRequests();
	void StopListeningRequests();
		
	ConnectionBroadcaster Connection_Broadcaster;
	boost::asio::io_context Connection_Context;
	boost::asio::io_context Connection_Loop_Context;
	std::unique_ptr<boost::asio::ip::tcp::endpoint> Server_Endpoint;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> Acceptor;
	std::unique_ptr<boost::asio::ip::tcp::socket> Connection_Socket;

	boost::asio::io_context Switch_Request_Context;
	boost::asio::io_context Switch_Loop_Context;
	boost::asio::io_context Pointer_Request_Context;
	boost::asio::io_context Pointer_Loop_Context;
	std::unique_ptr<boost::asio::ip::tcp::socket> Switch_Request_Socket;
	std::unique_ptr<boost::asio::ip::tcp::socket> Pointer_Request_Socket;
	std::unique_ptr<std::thread>Switch_Request_Thread;
	std::unique_ptr<std::thread>Pointer_Request_Thread;

	void ListenSwitchRequest();
	void ListenPointerRequest();

	bool Connected = false;
	bool KeepAlive = true;
	std::function<void()> Cancel_Connection;

	bool Should_Hear_Requests = false;

	PointerRequestReceiver Pointer_Request_Receiver;
	SwitchRequestReceiver Switch_Request_Receiver;
};