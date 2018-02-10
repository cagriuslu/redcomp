#include "redcomp/asm/LabelStorage.hh"

const std::regex labelLineIdentifier("^([_a-zA-Z][_a-zA-Z0-9]*):$", std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize);

bool redcomp::LabelStorage::insert(std::string line, uint64_t address)
{
	std::smatch matches;
	if (std::regex_search(line, matches, labelLineIdentifier))
	{
		labels[matches[1].str()] = address;
		return true;
	}
	return false;
}

std::pair<bool,uint64_t> redcomp::LabelStorage::retrieve(std::string label)
{
	auto it = labels.find(label);
	if (it != labels.end())
		return std::make_pair(true, it->second);
	else
		return std::make_pair(false, 0);
}

bool redcomp::LabelStorage::isLabel(std::string line)
{
	return std::regex_search(line, labelLineIdentifier);
}
