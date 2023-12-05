#include "Logger.h"

// STD Includes
#include <iostream>
#include <ranges>
#include <algorithm>

//Windows Includes
#ifdef _CONSOLE
#include <conio.h>
#endif

constexpr auto CLEAR_LINE = "\u001b[1F\u001b[2k";

std::string Logger::Last_Replaced_Message = std::string();
uint32_t Logger::Replaceble_Message_Lines = 0;
bool Logger::Replace = false;

void Logger::UpdateMessage(std::string message, bool end_replace)
{
    if (!end_replace && Replace)
    {
        CleanLines(Replaceble_Message_Lines + 1);

        message.append("\n").append(Last_Replaced_Message);
        std::cout << message.c_str();
    }
    else
    {
        Replace = false;
        message.append("\n");
        std::cout << message.c_str();
    }
}

void Logger::ReplacebleMessage(std::string message)
{
    uint32_t lines = std::ranges::count(message, '\n');
    message.append("\n");

    CleanLines(Replaceble_Message_Lines + 1);
    Last_Replaced_Message = message;
    std::cout << message.c_str();

    Replace = true;
    Replaceble_Message_Lines = lines;
}

bool Logger::AcceptQuestion(std::string question, bool append_replace)
{
    question.append("\n Press Y for yes, and N for no:\n");
    
    if (append_replace)
    {
        Replaceble_Message_Lines += std::ranges::count(question, '\n');
        Last_Replaced_Message.append(question);
        UpdateMessage(Last_Replaced_Message, true);
    }
    else
    {
        Replace = false;
        UpdateMessage(question);
    }

    char option = NULL;
    while (true)
    {
        option = _getch();
        if (option == 'y' || option == 'Y')
        {
            return true; // Yes
        }
        if (option == 'n' || option == 'N')
        {
            return false; // No
        }
    }
}

void Logger::OptionQuestion(std::string question, bool append_replace, std::function<bool(char)> validate_callback)
{
    if (append_replace)
    {
        Replaceble_Message_Lines += std::ranges::count(question, '\n');
        Last_Replaced_Message.append(question);
        UpdateMessage(Last_Replaced_Message, true);
    }
    else
    {
        Replace = false;
        UpdateMessage(question);
    }

    char option = NULL;
    do
    {
        option = _getch();
    } while (!validate_callback(option));
}

void Logger::CleanLines(uint32_t lines)
{
    std::string clear_line;
    for (uint32_t i = 0; i < lines; i++)
    {
        clear_line.append(CLEAR_LINE);
    }
    std::cout << clear_line.c_str();
}