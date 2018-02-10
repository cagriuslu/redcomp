#pragma once

#include "Utils.hh"
#include "../common/instruction.h"
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

namespace redcomp
{
	class Instruction
	{
	public:
		static std::pair<bool,std::vector<uint8_t>> parse(std::string line);
	};
}
