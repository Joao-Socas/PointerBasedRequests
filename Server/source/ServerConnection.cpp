#include "iostream"
#include "boost/bind.hpp"

#include "ServerConnection.h"

constexpr auto TIMEOUT_LIMIT = boost::posix_time::millisec(600);
constexpr auto BROADCAST_INTERVAL = std::chrono::milliseconds(1000);
constexpr int PORT = 27652;
constexpr IPVersion IP_Version = IPVersion::IPV4;

ServerConnection::ServerConnection(std::function<void()>& cancel_connection) : Cancel_Connection(cancel_connection), Connection_Broadcaster(PORT)
{
	Server_Endpoint = std::make_unique <boost::asio::ip::tcp::endpoint>(boost::asio::ip::tcp::v4(), PORT);
	Acceptor = std::make_unique <boost::asio::ip::tcp::acceptor>(Connection_Context, *Server_Endpoint.get());
}

void ServerConnection::StartConnection() 
{
	Connection_Loop_Context.post(boost::bind(&ServerConnection::WaitForConnection, this));
	Connection_Loop_Context.restart();
	Connection_Loop_Context.run();
}

void ServerConnection::WaitForConnection()
{
	Connection_Broadcaster.StartBroadcastIP();
	if (Connection_Socket.get() && Connection_Socket->is_open())
	{
		Connection_Socket->cancel();
		Connection_Socket->close(); // Just for safety
	}
	Logger::UpdateMessage("Waiting connection...");
	Acceptor->listen();
	boost::system::error_code connection_error;
	Acceptor->async_accept(Connection_Context, [this, &connection_error](const boost::system::error_code& error, boost::asio::ip::tcp::socket new_socket)
	{
		connection_error = error;
		Connection_Socket = std::make_unique<boost::asio::ip::tcp::socket>(std::move(new_socket));
	});
	Connection_Context.restart();
	Connection_Context.run();

	if (connection_error)
	{
		Logger::UpdateMessage(std::string("Accepting connection start error: ").append(connection_error.what()));
	}
	if (Connection_Socket->is_open())
	{
		Connection_Socket->set_option(boost::asio::ip::tcp::no_delay(true));
		ConnectionProposal();
	}
	Connection_Loop_Context.post(boost::bind(&ServerConnection::WaitForConnection, this));
}

void ServerConnection::CancelConnection()
{
	Sync_ID++;
	if (Connection_Broadcaster.Is_Broadcasting)
	{
		Connection_Broadcaster.StopBroadcastIP();
	}
	if (Connection_Socket)
	{
		Connection_Socket->close();
	}
	Acceptor->cancel();
	Acceptor->close();
}



void ServerConnection::ConnectionProposal()
{
	Connection_Broadcaster.StopBroadcastIP();
	const int buffer_size = sizeof(ClientConnectionParams);
	char buffer[buffer_size];

	Logger::UpdateMessage("Receiving connection proposal.");

	if (!TimeoutRead(*Connection_Socket, Connection_Context, buffer, buffer_size))
	{
		Logger::UpdateMessage("Failed to receive connection proposal data.");
		return;
	}

	ConnectionProposalCheck(buffer);
}


bool ServerConnection::TimeoutRead(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, char* buffer, std::size_t buffer_size)
{
	boost::asio::deadline_timer timer(io_context);
	bool in_time = true;
	bool can_timeout = true;
	bool cancelled = false;

	boost::system::error_code connection_error;
	// Start the timer
	timer.expires_from_now(TIMEOUT_LIMIT);
	timer.async_wait([&socket, &in_time, &can_timeout](const boost::system::error_code& error_code)
		{
			if (can_timeout)
			{
				in_time = false;
				socket.cancel();
			}
		});

	Cancel_Connection = [&socket, &timer, &cancelled]()
		{
			socket.cancel();
			timer.cancel();

			cancelled = true;
		};

	boost::asio::async_read(socket, boost::asio::buffer(buffer, buffer_size), [&timer, &in_time, &can_timeout, &connection_error](const boost::system::error_code& error_code, std::size_t)
		{
			if (in_time)
			{
				can_timeout = false;
				timer.cancel();
				connection_error = error_code;
			}
		});
	io_context.restart();
	io_context.run();
	if (cancelled)
	{
		return false;
	}
	else if (!in_time)
	{
		Logger::UpdateMessage("Connection timed out! The chosen connection target did not respond.");
		return false;
	}
	else if (connection_error)
	{
		Logger::UpdateMessage(std::string("A connection error ocurred: ").append(connection_error.what()));
		return false;
	}

	return true;
};

void ServerConnection::ConnectionProposalCheck(char* buffer)
{
	ClientConnectionParams Client_Params;
	memcpy(&Client_Params, buffer, sizeof(Client_Params));
	boost::system::error_code connection_error;
	char answer_buffer = Logger::AcceptQuestion(std::string("Accept connection from client ").append(Client_Params.Friendly_Name)); //TODO change this if negate is a possibility
	boost::asio::async_write(*Connection_Socket.get(), boost::asio::buffer(&answer_buffer, 1), [&connection_error](const boost::system::error_code& error, std::size_t)
	{
			connection_error = error;
	});
	Connection_Context.restart();
	Connection_Context.run();

	if (!connection_error)
	{
		Connected = true;
		Logger::UpdateMessage("Connected");

		Acceptor->async_accept(Connection_Context, [this, &connection_error](const boost::system::error_code& error, boost::asio::ip::tcp::socket new_socket)
			{
				connection_error = error;
				Pointer_Request_Socket = std::make_unique<boost::asio::ip::tcp::socket>(std::move(new_socket));
			});
		Connection_Context.restart();
		Connection_Context.run();
		Acceptor->async_accept(Connection_Context, [this, &connection_error](const boost::system::error_code& error, boost::asio::ip::tcp::socket new_socket)
			{
				connection_error = error;
				Switch_Request_Socket = std::make_unique<boost::asio::ip::tcp::socket>(std::move(new_socket));
			});
		Connection_Context.restart();
		Connection_Context.run();


        ScoutConnection();
	}
	if (connection_error)
	{
		Logger::UpdateMessage(std::string("Connection error: ").append(connection_error.what()));
	}
}

void ServerConnection::ScoutConnection()
{
	char buffer = (char)true;
	while (KeepAlive)
	{
		boost::system::error_code error;
		boost::asio::write(*Connection_Socket.get(), boost::asio::buffer(&buffer, 1), error);
		if (error)
		{
			Connected = false;
			std::cout << error.what().c_str() << '\n';
			return;
		}

		if (!TimeoutRead(*Connection_Socket, Connection_Context, &buffer, sizeof(char)))
		{
			return;
		}

		boost::asio::deadline_timer timer(Connection_Context);
		timer.expires_from_now(TIMEOUT_LIMIT/2);
		timer.wait();
	}
}
