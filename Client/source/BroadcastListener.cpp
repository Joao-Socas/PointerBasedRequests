#include "BroadcastListener.h"

// STD Includes
#include <string>
#include <sstream>
#include <memory>
// Boost Includes
#include "boost/bind.hpp"
// Common Includes
#include "Logger.h"

constexpr auto BROADCAST_LIMIT = boost::posix_time::millisec(1200);

BroadcastListener::BroadcastListener(uint32_t port) : Port(port)
{
    Client_Broadcast_Endpoint = std::make_unique<boost::asio::ip::udp::endpoint>(boost::asio::ip::address_v4::any(), Port);
}

void BroadcastListener::ListenBroadcast()
{
    Should_Listen_Broadcast = true;
    Broadcast_Thread_Context.post(boost::bind(&BroadcastListener::ListenBroadcastThread, this));
    Broadcast_Thread = std::make_unique<std::thread>([this]()
    {
        Broadcast_Thread_Context.restart();
        Broadcast_Thread_Context.run();
    });
}

void BroadcastListener::StopListeningBroadcast()
{
    Should_Listen_Broadcast = false;
    Broadcast_Thread->join();
}

BroadcastData BroadcastListener::ChooseServer()
{
    char selected_id;
    std::function<bool(char)>validate_callback = [this, &selected_id](char option) {
        if (option == 'x')
        {
            selected_id = -1;
            return true; // EXIT
        }
        if (option > 47 && option < 58 && (option - 48) < Broadcast_Poll.size())
        {
            selected_id = option - 48;
            return true;
        }
        return false;
    };

    Logger::OptionQuestion("Select one server to connect or x to exit: ", true, validate_callback);
    return selected_id == -1 ? BroadcastData() : Broadcast_Poll[selected_id];
}

void BroadcastListener::ListenBroadcastThread()
{
    char port_char[6];
    sprintf_s(port_char, "%ld", Port);
    auto endpoints = Self_Resolver.resolve(boost::asio::ip::host_name(), port_char);

    Broadcast_Socket = std::make_unique<boost::asio::ip::udp::socket>(Broadcast_Listen_Context);
    boost::system::error_code error_code;
    Broadcast_Socket->open(boost::asio::ip::udp::v4(), error_code);
    if (error_code)
    {
        Logger::UpdateMessage(std::string("A error occurred when oppening broadcast socket: ").append(error_code.what()));
        return;
    }
    Broadcast_Socket->set_option(boost::asio::socket_base::broadcast(true));
    Broadcast_Socket->bind(*Client_Broadcast_Endpoint.get());

    int32_t broadcast_data_size = sizeof(BroadcastData);
    char* buffer = new char[broadcast_data_size];
    BroadcastData broadcast_data;
    std::vector<BroadcastData> valid_servers;

    // This is a time loop to clear the valid_server pool if no server is found in the BROADCAST_LIMIT duration
    boost::asio::deadline_timer timer(Broadcast_Listen_Context);

    Is_Listening_Broadcast = true;
    while (Should_Listen_Broadcast)
    {
        timer.expires_from_now(BROADCAST_LIMIT);
        timer.async_wait([&valid_servers, this](boost::system::error_code error)
            {
                if (!error && Should_Listen_Broadcast)
                {
                    valid_servers.clear();
                    Broadcast_Poll = valid_servers;
                }
            });

        ShowBroadcastPoll();
        boost::asio::ip::udp::endpoint broadcast_server_endpoint;
        // Even though the HMD probably only connects to one network at a time, it can have a ipv4 and ipv6 endpoint
        for (auto endpoint_iteration = endpoints.begin(); endpoint_iteration != endpoints.end(); endpoint_iteration++)
        {
            if (endpoint_iteration->endpoint().address().is_v4())
            {
                std::string broadcast_adress_string = endpoint_iteration->endpoint().address().to_string();
                // Replaces de last of the adress with 255
                for (int i = 1; i < broadcast_adress_string.size() - broadcast_adress_string.find_last_of('.');)
                {
                    broadcast_adress_string.pop_back();
                }
                broadcast_adress_string.append("255");

                broadcast_server_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(broadcast_adress_string), Port);
            }
        }

        std::size_t recieved_data_size = 0;
        Broadcast_Socket->async_receive_from(boost::asio::buffer(buffer, broadcast_data_size), broadcast_server_endpoint,
            [&recieved_data_size, &error_code, &timer, this](const boost::system::error_code& error, std::size_t bytes_transferred)
            {
                if (Should_Listen_Broadcast)
                {
                    timer.cancel();
                    recieved_data_size = bytes_transferred;
                    error_code = error;
                }
            });
        Broadcast_Listen_Context.restart();
        Broadcast_Listen_Context.run();

        if (error_code && Should_Listen_Broadcast)
        {
            Logger::UpdateMessage(std::string("A error occurred when receiving broadcast: ").append(error_code.what()));
            return;
        }

        if (recieved_data_size != broadcast_data_size)
        {
            continue;
        }

        memcpy(&broadcast_data, buffer, broadcast_data_size);

        if (std::find(valid_servers.begin(), valid_servers.end(), broadcast_data) != valid_servers.end())
        {
            Broadcast_Poll = valid_servers;
            valid_servers.clear();
        }
        valid_servers.push_back(broadcast_data);
    }
    Is_Listening_Broadcast = false;
}

void BroadcastListener::ShowBroadcastPoll()
{
    std::stringstream broadcast_stream;
    for (int i = 0; i < Broadcast_Poll.size(); i++)
    {
        broadcast_stream << i <<": " << Broadcast_Poll[i].Host_Name << " IP:" << Broadcast_Poll[i].Server_IP_Adress << '\n';
    }
    if (Broadcast_Poll.size() == 0)
    {
        broadcast_stream << "No available server was found!" << '\n';
    }
   
    Logger::ReplacebleMessage(broadcast_stream.str());
}