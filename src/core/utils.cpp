#include "utils.h"

#include <spdlog/spdlog.h>
#include <sstream>
#include <Windows.h>

namespace BerylEngine
{
	bool isDebuggerPresent()
	{
		return IsDebuggerPresent();
	}

	void debugBreak()
	{
		if (isDebuggerPresent())
			DebugBreak();
	}

	void fatal(const char* msg, const char* file, int line)
	{
		spdlog::critical("{}({}): {}", file, line, msg);

		debugBreak();
		std::terminate();
	}

	std::vector<std::string> splitstr(const std::string& str, char delim)
	{
		std::vector<std::string> splitted;

		std::istringstream stream(str);
		std::string word;
		while (std::getline(stream, word, delim))
			splitted.push_back(word);

		return splitted;
	}
}