#include "ClientConnection.h"

// STD Includes
#include <conio.h>
#include <functional>
#include <iostream>
#include <cstdint>
// Boost Includes
#include "boost/bind.hpp"
// Common Includes
#include "Logger.h"

constexpr uint32_t PORT = 27652;
constexpr auto TIMEOUT_LIMIT = boost::posix_time::millisec(600);


ClientConnection::ClientConnection() : Broadcast_Listener(PORT)
{
    BroadcastData target_server;
    while (!Connected && !Exiting)
    {

        Broadcast_Listener.ListenBroadcast();
        target_server = Broadcast_Listener.ChooseServer();
        Broadcast_Listener.StopListeningBroadcast();
        Connect(target_server);
    }
}

ClientConnection::~ClientConnection()
{
    if (Broadcast_Listener.Is_Listening_Broadcast)
    {
        Broadcast_Listener.StopListeningBroadcast();
    }
}

void ClientConnection::Connect(BroadcastData broadcast_data)
{
    Server_Socket = std::make_unique<boost::asio::ip::tcp::socket>(Connection_Context);
    bool cancel_connection = false;
    //Cancel_Connection = [this, &cancel_connection]()
    //{
    //    cancel_connection = true;
    //    Server_Socket->close();
    //};

    Server_Endpoint = std::make_unique<boost::asio::ip::tcp::endpoint>(boost::asio::ip::address::from_string(broadcast_data.Server_IP_Adress), broadcast_data.Server_Port);
    if (!TimeoutConnect(*Server_Socket, Connection_Context, *Server_Endpoint) /*|| cancel_connection*/)
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
        if (!cancel_connection)
            Logger::UpdateMessage(std::string("A connection error ocurred: ").append(connection_error.what()));
        Connected = false;
        return;
    }

    char accepted = false;

    boost::asio::async_read(*Server_Socket, boost::asio::buffer(&accepted, 1), [&connection_error](const boost::system::error_code& error_code, std::size_t)
    {
        connection_error = error_code;
    });
    Connection_Context.restart();
    Connection_Context.run();

    if (connection_error || cancel_connection)
    {
        if (!cancel_connection)
            Logger::UpdateMessage(std::string("A connection error ocurred: ").append(connection_error.what()));
        Connected = false;
        return;
    }

    if ((bool)accepted)
    {
        Logger::UpdateMessage("Connected to server!");
        TimeoutConnect(*Pointer_Request_Socket, Request_Context, *Server_Endpoint);
        TimeoutConnect(*Switch_Request_Socket, Request_Context, *Server_Endpoint);
        Keep_Server_Connection_Alive_Thread = std::make_unique<std::thread>(&ClientConnection::KeepServerConnectionAlive, this);
        Connected = true;
        return;
    }
    Logger::UpdateMessage("Connection denied by the server!");
    Connected = false;
    return;
}

void ClientConnection::PointerRequestSend(char* buffer, std::size_t buffer_size)
{
    boost::system::error_code connection_error;
    boost::asio::write(*Pointer_Request_Socket, boost::asio::buffer(&buffer, buffer_size), connection_error);
    if (connection_error)
    {
        Logger::UpdateMessage(std::string("Error making pointer request: ").append(connection_error.what()).c_str());
    }
}

void ClientConnection::SwitchRequestSend(char* buffer, std::size_t buffer_size)
{
    boost::system::error_code connection_error;
    boost::asio::write(*Switch_Request_Socket, boost::asio::buffer(&buffer, buffer_size), connection_error);
    if (connection_error)
    {
        Logger::UpdateMessage(std::string("Error making switch request: ").append(connection_error.what()).c_str());
    }
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

    //Cancel_Connection = [&socket, &timer, &cancelled]()
    //    {
    //        socket.cancel();
    //        timer.cancel();

    //        cancelled = true;
    //    };

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
        Logger::UpdateMessage("Connection timed out! The chosen connection target did not respond.");
        return false;
    }
    else if (connection_error)
    {
        Logger::UpdateMessage(std::string("A connection error ocurred: ").append(connection_error.what()));
        return false;
    }

    return true;
}

void ClientConnection::KeepServerConnectionAlive()
{
    bool cancel_connection = false;
    //Cancel_Connection = [this, &cancel_connection]()
    //{
    //    cancel_connection = true;
    //    Server_Socket->cancel();
    //};

    char buffer = (char)true;
    while (cancel_connection == false)
    {
        boost::system::error_code connection_error;

        boost::asio::write(*Server_Socket, boost::asio::buffer(&buffer, 1), connection_error);
        if (connection_error)
        {
            if (!cancel_connection)
                Logger::UpdateMessage(std::string("A connection error ocurred: ").append(connection_error.what()));
            return;
        }

        TimeoutRead(*Server_Socket, Connection_Context, &buffer, 1);
        boost::asio::deadline_timer timer(Connection_Context);
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

    //Cancel_Connection = [&socket, &timer, &cancelled]()
    //    {
    //        socket.cancel();
    //        timer.cancel();

    //        cancelled = true;
    //    };

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
}
