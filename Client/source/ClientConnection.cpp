#include "ClientConnection.h"

// STD Includes
#include <conio.h>
#include <functional>
#include <iostream>
#include "boost/bind.hpp"

constexpr int PORT = 27652;
constexpr auto BROADCAST_LIMIT = boost::posix_time::millisec(1200);
constexpr auto TIMEOUT_LIMIT = boost::posix_time::millisec(600);


ClientConnection::ClientConnection(std::function<void()>& cancel_connection) : Cancel_Connection(cancel_connection)
{
    Client_Broadcast_Endpoint = std::make_unique<boost::asio::ip::udp::endpoint>(boost::asio::ip::address_v4::any(), PORT);
    BroadcastData target_server;

    cancel_connection = [this] {Exiting = true; };

    while (!Connected && !Exiting)
    {
        ChooseServer(target_server);
        if (Exiting)
        {
            continue;
        }
        StartConnection(target_server);
    }
}

ClientConnection::~ClientConnection()
{
    if (Should_Hear_Broadcast)
    {
        StopHearingBroadcast();
        if (Broadcast_Socket)
        {
            Broadcast_Socket->close();
        }
    }
}

void ClientConnection::ChooseServer(BroadcastData& target_server)
{
    HearBroadcast();
    Exiting = !GetBroadcastSellection(target_server); // Exiting becomes true if x was selected
    StopHearingBroadcast();
}

void ClientConnection::StartConnection(BroadcastData& target_server)
{
    std::thread connection_thread(&ClientConnection::Connect, this, target_server);
    // TODO this is where we would get the input to cancel connection, not implemented in this mocked version
    if (Exiting)
    {
        Cancel_Connection();
    }
    connection_thread.join();
}


void ClientConnection::HearBroadcast()
{
    Should_Hear_Broadcast = true;
    Broadcast_IO_Context.post(boost::bind(&ClientConnection::HearBroadcastThread, this));
    Broadcast_Thread = std::make_unique<std::thread>([this]() 
        {
            Broadcast_IO_Context.restart();
            Broadcast_IO_Context.run();
        });
};

void ClientConnection::ShowBroadcastPoll()
{
    std::cout << "\u001b[1J" << "\u001b[u";

    for (int i = 0; i < Broadcast_Poll.size(); i++)
    {
        std::cout << "0: " << Broadcast_Poll[i].Host_Name << " IP:" << Broadcast_Poll[i].Server_IP_Adress << '\n';
    }
    if (Broadcast_Poll.size() == 0)
    {
        std::cout << "No available server was found!" << '\n';
    }

    std::cout << '\n' << '\n' << "Select a server, or type x to exit:" << '\n';
}

bool ClientConnection::GetBroadcastSellection(BroadcastData& target_server)
{
    char option = NULL;
    while (true)
    {
        option = _getch();
        if (option == 'x')
        {
            return false; // EXIT
        }
        if (option > 47 && option < 58 && (option - 48) < Broadcast_Poll.size())
        {
            target_server = Broadcast_Poll[option - 48];
            return true;
        }
    }
}

void ClientConnection::HearBroadcastThread()
{
    if (!Should_Hear_Broadcast)
    {
        return;
    }
    char port_char[6];
    sprintf_s(port_char, "%ld", PORT);
    auto endpoints = Self_Resolver.resolve(boost::asio::ip::host_name(), port_char);

    Broadcast_Socket = std::make_unique<boost::asio::ip::udp::socket>(Server_IO_Context);
    boost::system::error_code error_code;
    Broadcast_Socket->open(boost::asio::ip::udp::v4(), error_code);
    if (error_code)
    {
        BroadcastError(error_code.what());
        return;
    }
    Broadcast_Socket->set_option(boost::asio::socket_base::broadcast(true));
    Broadcast_Socket->bind(*Client_Broadcast_Endpoint.get());

    int32_t broadcast_data_size = sizeof(BroadcastData);
    char* buffer = new char[broadcast_data_size];
    BroadcastData broadcast_data;
    std::vector<BroadcastData> valid_servers;

    // This is a time loop to clear the valid_server pool if no server is found in the BROADCAST_LIMIT duration
    boost::asio::deadline_timer timer(Server_IO_Context);

    while (Should_Hear_Broadcast) 
    {
        timer.expires_from_now(BROADCAST_LIMIT);
        timer.async_wait([&valid_servers, this](boost::system::error_code error)
        { 
            if (!error && Should_Hear_Broadcast)
            {
                valid_servers.clear();
                Broadcast_Poll = valid_servers;
                ShowBroadcastPoll();
            }
        });

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

                broadcast_server_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(broadcast_adress_string), PORT);
            }
        }

        std::size_t recieved_data_size = 0;
        Broadcast_Socket->async_receive_from(boost::asio::buffer(buffer, broadcast_data_size), broadcast_server_endpoint,
            [&recieved_data_size, &error_code, &timer, this](const boost::system::error_code& error, std::size_t bytes_transferred)
            {
                if (Should_Hear_Broadcast)
                {
                    timer.cancel();
                    recieved_data_size = bytes_transferred;
                    error_code = error;
                }
            });
        Server_IO_Context.restart();
        Server_IO_Context.run();

        if (error_code && Should_Hear_Broadcast)
        {
            BroadcastError(error_code.what());
            return;
        }

        if (recieved_data_size != broadcast_data_size)
        {
            continue;
        }

        memcpy(&broadcast_data, buffer, broadcast_data_size);
        if (broadcast_data.Lince_Validation != 'l' + 'i' + 'n' + 'c' + 'e')
        {
            continue;
        }

        if (std::find(valid_servers.begin(), valid_servers.end(), broadcast_data) != valid_servers.end())
        {
            Broadcast_Poll = valid_servers;
            ShowBroadcastPoll();
            valid_servers.clear();
        }
        valid_servers.push_back(broadcast_data);
    }
}

void ClientConnection::BroadcastError(std::string broadcast_error)
{
    std::cout << "Error finding servers: " << '\n';
    std::cout << "Retry in 5 seconds. Press x to cancel and exit." << '\n';
    for (int i = 10; i > 0; i--)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "\u001b[1M Retry in " << std::to_string(i / 2) << " seconds.Press x to cancel and exit." << '\n';
    }
    if (Should_Hear_Broadcast)
    {
        Broadcast_IO_Context.post(boost::bind(&ClientConnection::HearBroadcastThread, this));
    }
}

void ClientConnection::StopHearingBroadcast()
{
    Should_Hear_Broadcast = false;
    if (Broadcast_Socket)
    {
        Broadcast_Socket->close();
    }
    Broadcast_Thread->join(); // TODO Fazer o async join
}

void ClientConnection::Connect(BroadcastData broadcast_data)
{
    Server_Socket = std::make_unique<boost::asio::ip::tcp::socket>(Server_IO_Context);
    bool cancel_connection = false;
    Cancel_Connection = [this, &cancel_connection]()
    {
        cancel_connection = true;
        Server_Socket->close();
    };

    Server_Endpoint = std::make_unique<boost::asio::ip::tcp::endpoint>(boost::asio::ip::address::from_string(broadcast_data.Server_IP_Adress), broadcast_data.Server_Port);
    if (!TimeoutConnect(*Server_Socket, Server_IO_Context, *Server_Endpoint) || cancel_connection)
    {
        Connected = false;
        return;
    }
    
    strcpy_s(ConnectionParams.Friendly_Name, boost::asio::ip::host_name().c_str());
    const int buffer_size = sizeof(ConnectionParams);
    char buffer[buffer_size];
    memcpy(buffer, &ConnectionParams, buffer_size);
    boost::system::error_code connection_error;
    boost::asio::write(*Server_Socket, boost::asio::buffer(&buffer, buffer_size), connection_error);

    if (connection_error || cancel_connection)
    {
        if (!cancel_connection) std::cout << connection_error.what().c_str() << '\n';
        Connected = false;
        return;
    }

    char accepted = false;

    boost::asio::async_read(*Server_Socket, boost::asio::buffer(&accepted, 1), [&connection_error](const boost::system::error_code& error_code, std::size_t)
    {
        connection_error = error_code;
    });
    Server_IO_Context.restart();
    Server_IO_Context.run();

    if (connection_error || cancel_connection)
    {
        if (!cancel_connection) std::cout << connection_error.what().c_str() << '\n';
        Connected = false;
        return;
    }

    if ((bool)accepted)
    {
        std::cout << "Connected to server!" << '\n';
        Keep_Server_Connection_Alive_Thread = std::make_unique<std::thread>(&ClientConnection::KeepServerConnectionAlive, this);
        Connected = true;
        return;
    }
    std::cout << "Connection denied by the server!" << '\n';
    Connected = false;
    return;
}

bool ClientConnection::TimeoutConnect(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint& endpoint)
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

    socket.async_connect(endpoint, [&timer, &in_time, &can_timeout, &connection_error](const boost::system::error_code& error_code)
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
        std::cout << "Connection timed out! The chosen connection target did not respond." << '\n';
        return false;
    }
    else if (connection_error)
    {
        std::cout << "A connection error ocurred: " << connection_error.what().c_str() << '\n';
        return false;
    }

    return true;
}

void ClientConnection::KeepServerConnectionAlive()
{
    bool cancel_connection = false;
    Cancel_Connection = [this, &cancel_connection]()
    {
        cancel_connection = true;
        Server_Socket->cancel();
    };

    char buffer = (char)true;
    while (cancel_connection == false)
    {
        boost::system::error_code connection_error;

        boost::asio::write(*Server_Socket, boost::asio::buffer(&buffer, 1), connection_error);
        if (connection_error)
        {
            if (!cancel_connection) std::cout << connection_error.what().c_str() << '\n';
            return;
        }

        TimeoutRead(*Server_Socket, Server_IO_Context, &buffer, 1);
        boost::asio::deadline_timer timer(Server_IO_Context);
        timer.expires_from_now(TIMEOUT_LIMIT / 2);
        timer.wait();
    }
}

bool ClientConnection::TimeoutRead(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io_context, char* buffer, std::size_t buffer_size)
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
        std::cout << "Connection timed out! The chosen connection target did not respond." << '\n';
        return false;
    }
    else if (connection_error)
    {
        std::cout << "A connection error ocurred: " << connection_error.what().c_str() << '\n';
        return false;
    }

    return true;
}
