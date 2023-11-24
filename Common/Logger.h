#pragma once
// STD Icludes
#include <string>
#include <cstdint>

class Logger
{
public:
	static void UpdateMessage(std::string message, bool end_replace = false);
	static void ReplacebleMessage(std::string message);
	static void AcceptQuestion(std::string question);

private:
	static void CleanLines(uint32_t lines);
	static std::string Last_Replaced_Message;
	static uint32_t Replaceble_Message_Lines;
	static bool Replace;
};