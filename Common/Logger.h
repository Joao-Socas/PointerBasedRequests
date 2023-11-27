#pragma once
// STD Icludes
#include <string>
#include <cstdint>
#include <functional>


class Logger
{
public:
	static void UpdateMessage(std::string message, bool end_replace = false);
	static void ReplacebleMessage(std::string message);
	static bool AcceptQuestion(std::string question, bool append_replace = false);
	static bool OptionQuestion(std::string question, bool append_replace, std::function<bool(char)>validate_callback);

private:
	static void CleanLines(uint32_t lines);
	static std::string Last_Replaced_Message;
	static uint32_t Replaceble_Message_Lines;
	static bool Replace;
};