#pragma once

#include <cstdint>
#include <map>
#include <vector>

namespace redcomp
{
	class SegmentStorage
	{
	public:
		std::vector< std::pair< uint64_t,std::vector<uint8_t> > > segments;
	public:
		void createNew(uint64_t);
		bool insert(std::vector<uint8_t>&);
	};
}
