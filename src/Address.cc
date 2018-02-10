#include "redcomp/asm/Address.hh"

const std::regex addressLineIdentifier("^([-+]?\\d+|[-+]?0[xX][\\da-fA-F]+|[-+]?0[bB][01]+):$", std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize);

bool redcomp::Address::isAddress(std::string line)
{
	return std::regex_search(line, addressLineIdentifier);
}

uint64_t redcomp::Address::getAddress(std::string line)
{
	std::smatch matches;
	if (std::regex_search(line, matches, addressLineIdentifier))
	{
		return Utils::strToU64(matches[1].str());
	}
	return 0;
}
