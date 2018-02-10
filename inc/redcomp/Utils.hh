#pragma once

#include <cctype>
#include <string>

namespace redcomp
{
	class Utils
	{
	public:
		static void trimLeft(std::string &s);
		static void trimRight(std::string &s);
		static char firstNonspaceChar(std::string &s);
		static bool isValidIdentifier(std::string &s);
		static uint64_t strToU64(std::string s);
	};
}