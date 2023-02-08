#include "utils.h"

#include <sstream>

namespace BerylEngine
{
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