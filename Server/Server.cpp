// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ServerConnection.h"

int main()
{
    ServerConnection connection;
    connection.StartConnection();
    std::getchar();
}

