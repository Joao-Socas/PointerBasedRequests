#include "Logger.h"

// STD Includes
#include <iostream>
#include <algorithm>

constexpr auto CLEAR_LINE = "\u001b[2k\u001b[1F";

std::string Logger::Last_Replaced_Message = NULL;
uint32_t Logger::Replaceble_Message_Lines = 0;
bool Logger::Replace = false;

void Logger::UpdateMessage(std::string message, bool end_replace = false)
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

void Logger::AcceptQuestion(std::string question)
{
    Replace = false;
    question.append("\n Press Y for yes, and N for no:\n");

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

