#include "redcomp/asm/Utils.hh"

void redcomp::Utils::trimLeft(std::string &s)
{
	size_t firstNonspaceIdx = 0;
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (!std::isspace(s[i]))
		{
			firstNonspaceIdx = i;
			break;
		}
	}
	s = s.substr(firstNonspaceIdx);
}

void redcomp::Utils::trimRight(std::string &s)
{
	size_t lastSpaceIdx = 0;
	for (size_t i = s.length(); i-- > 0; )
	{
		if (!std::isspace(s[i]))
		{
			lastSpaceIdx = i+1;
			break;
		}
	}
	s.resize(lastSpaceIdx);
}

char redcomp::Utils::firstNonspaceChar(std::string &s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (!std::isspace(s[i]))
			return s[i];
	}
	return 0;
}

bool redcomp::Utils::isValidIdentifier(std::string &s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		if (i == 0 && std::isdigit(c))
			return false;

		if (std::isdigit(c) || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_')
			continue;
		else
			return false;
	}
	return true;
}

uint64_t redcomp::Utils::strToU64(std::string s)
{
	bool negative = false;

	int i = 0;
	if (s[i] == '-')
	{
		++i;
		negative = true;
	}
	else if (s[i] == '+')
	{
		++i;
	}
	s = s.substr(i);

	if (2 < s.length() && (s[1] == 'h' || s[1] == 'H'))
	{
		// parse as hex
		s = s.substr(2);
		return std::stoull(s, 0, 16);
	}
	else if (2 < s.length() && (s[1] == 'b' || s[1] == 'B'))
	{
		// parse as bin
		s = s.substr(2);
		return std::stoull(s, 0, 2);
	}
	else
	{
		// parse as dec
		return std::stoull(s, 0, 10);
	}
}
