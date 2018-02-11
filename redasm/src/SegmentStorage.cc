#include "redcomp/asm/SegmentStorage.hh"

void redcomp::SegmentStorage::createNew(uint64_t address)
{
	segments.emplace_back(address, std::vector<uint8_t>());
}

bool redcomp::SegmentStorage::insert(std::vector<uint8_t> &bytes)
{
	if (segments.size() == 0)
		return false;

	segments.back().second.insert(segments.back().second.end(), bytes.begin(), bytes.end());
	return true;
}
