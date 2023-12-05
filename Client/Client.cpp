// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>

#include "Logger.h"
#include "ClientConnection.h"
#include "PointerRequester.h"
#include "SwitchRequester.h"

void SwitchRequestTest(SwitchRequester& switch_requester)
{
    switch_requester.MultipleRequestTest();
}

void PointerRequestTest(PointerRequester& pointer_requester)
{
    pointer_requester.MultipleRequestTest();
}

int main()
{
    ClientConnection connection;
    PointerRequester pointer_requester(connection.Request_Pointers, connection);
    SwitchRequester switch_requester(connection);

    uint32_t menu_option = 0;
    std::string menu_options;
    menu_options.append("Choose one of the tests:\n");
    menu_options.append("1 - Test simple switch requests\n");
    menu_options.append("2 - Test simple pointer requests\n");

    std::function<bool(char)>validate_callback = [&menu_option](char option) {
    if (option == 'x')
    {
        menu_option = -1;
        return true; // EXIT
    }
    if (option > 47 && option < 58 && (option - 48) < 3)
    {
        menu_option = option - 48;
        return true;
    }
    return false;
    };

    while (menu_option != -1)
    {
        //Logger::ReplacebleMessage(menu_options);
        Logger::OptionQuestion(menu_options, false, validate_callback);
        switch (menu_option)
        {
        case 1:
            SwitchRequestTest(switch_requester);
            break;
        case 2:
            PointerRequestTest(pointer_requester);
            break;
        default:
            break;
        }
    }
}