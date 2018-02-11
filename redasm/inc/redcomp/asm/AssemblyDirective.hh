#pragma once

#include <regex>
#include <string>
#include <vector>

namespace redcomp
{
	class AssemblyDirective
	{
	public:
		static bool isAssemblyDirective(std::string line);
		static std::pair<bool,std::vector<uint8_t>> parse(std::string line);
	};
}
