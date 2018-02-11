#pragma once

#include <map>
#include <regex>

namespace redcomp
{
	class LabelStorage
	{
		std::map<std::string,uint64_t> labels;
	public:
		bool insert(std::string line, uint64_t address);
		std::pair<bool,uint64_t> retrieve(std::string label);
	public:
		static bool isLabel(std::string);
	};
}
