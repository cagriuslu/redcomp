#pragma once

#include "../Utils.hh"
#include <regex>
#include <string>

namespace redcomp
{
	class Address
	{
	public:
		static bool isAddress(std::string);
		static uint64_t getAddress(std::string);
	};
}
