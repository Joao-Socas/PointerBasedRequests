#include "ConnectionBroadcaster.h"

// STD Includes
#include <memory>

// Common Inlcudes
#include "Logger.h"

constexpr auto BROADCAST_INTERVAL = std::chrono::milliseconds(1000);

ConnectionBroadcaster::ConnectionBroadcaster(uint32_t port) :
	Port(port)
{
	Broadcast_Endpoint = std::make_unique <boost::asio::ip::udp::endpoint>(boost::asio::ip::udp::v4(), Port);
}

void ConnectionBroadcaster::StartBroadcastIP()
{
	// Configs a broadcast socket and makes a endpoint to lan broadcast adress (255.255.255.255)
	Broadcast_Socket = std::make_unique<boost::asio::ip::udp::socket>(Server_Broadcast_Context);
	Broadcast_Socket->open(boost::asio::ip::udp::v4());
	Broadcast_Socket->set_option(boost::asio::socket_base::broadcast(true));
	Broadcast_Socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));

	Should_Broadcast = true;

	Broadcast_Thread = std::make_unique<std::thread>(&ConnectionBroadcaster::BroadcastIP, this);
}

void ConnectionBroadcaster::BroadcastIP()
{
	Is_Broadcasting = true;
	std::string broadcast_inform;
	while (Should_Broadcast)
	{
		broadcast_inform = boost::asio::ip::host_name().append(" broadcasting from ips:\n");
		// Resolves for it's own hostname, 
		char port_char[6];
		sprintf_s(port_char, "%ld", Port);
		auto endpoints = Self_Resolver.resolve(boost::asio::ip::host_name(), port_char);
		for (auto endpoint_iteration = endpoints.begin(); endpoint_iteration != endpoints.end(); endpoint_iteration++)
		{
			if (endpoint_iteration->endpoint().address().is_v4()) // in this example we will use just ipv4 for simplicity
			{
				std::string broadcast_adress_string = endpoint_iteration->endpoint().address().to_string();
				broadcast_inform.append(broadcast_adress_string).append("\n");
				// Replaces de last of the adress with 255
				for (int i = 1; i < broadcast_adress_string.size() - broadcast_adress_string.find_last_of('.');)
				{
					broadcast_adress_string.pop_back();
				}
				broadcast_adress_string.append("255");

				boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::from_string(broadcast_adress_string), Port);
				BroadcastData broadcast_data;
				strcpy_s(broadcast_data.Host_Name, boost::asio::ip::host_name().c_str());
				broadcast_data.Server_Port = Port;
				strcpy_s(broadcast_data.Server_IP_Adress, endpoint_iteration->endpoint().address().to_string().c_str());
				memcpy(&Broadcast_Buffer, &broadcast_data, sizeof(broadcast_data));
				boost::system::error_code broadcast_error;
				Broadcast_Socket->async_send_to(boost::asio::buffer(Broadcast_Buffer, sizeof(BroadcastData)), broadcast_endpoint, [&broadcast_error](boost::system::error_code error, std::size_t)
					{
						if (error)
						{
							std::string oerro = error.what();
							broadcast_error = error;
						}
					});
				Server_Broadcast_Context.restart();
				Server_Broadcast_Context.run();
				if (broadcast_error && Should_Broadcast)
				{
					Logger::UpdateMessage(std::string("Error sending broadcast: ").append(broadcast_error.what()));
				}
			}
		}
		Logger::ReplacebleMessage(broadcast_inform);
		std::this_thread::sleep_for(BROADCAST_INTERVAL);
	}
	Is_Broadcasting = false;
}

void ConnectionBroadcaster::StopBroadcastIP()
{
	Should_Broadcast = false;
	Broadcast_Socket->cancel();
	Broadcast_Socket->close();
	Broadcast_Thread->join();
	Logger::UpdateMessage("Stoped broadcasting.", true);
}