#include "redcomp/asm/Utils.hh"
#include "redcomp/asm/Address.hh"
#include "redcomp/asm/AssemblyDirective.hh"
#include "redcomp/asm/LabelStorage.hh"
#include "redcomp/asm/SegmentStorage.hh"
#include "redcomp/asm/Instruction.hh"
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#define PUSH_NOP() \
	do { \
		std::cerr << "Pushing nop instruction for alignment" << std::endl; \
		std::vector<uint8_t> tmp = {0x00, 0x00}; \
		segmentStorage.insert(tmp); \
		currentAddress += 2; \
		halfInst = false; \
	} while (0)

void print32(uint32_t n)
{
	uint8_t tmp = n;
	printf("%c", tmp);
	tmp = n >> 8;
	printf("%c", tmp);
	tmp = n >> 16;
	printf("%c", tmp);
	tmp = n >> 24;
	printf("%c", tmp);
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	// State
	uint64_t currentAddress = 0;

	// Storages
	redcomp::LabelStorage labelStorage;
	redcomp::SegmentStorage segmentStorage;
	segmentStorage.createNew(currentAddress);

	std::string line;
	size_t lineNo = 0;
	bool halfInst = false;
	while (std::getline(std::cin, line))
	{
		++lineNo;

//		std::cerr << "parsing:" << line << std::endl;
		// trim
		redcomp::Utils::trimRight(line);
		redcomp::Utils::trimLeft(line);
		// get rid of comment
		size_t octothorpLocation = line.find('#');
		if (octothorpLocation != std::string::npos)
			line = line.substr(0, octothorpLocation);
		if (line.length() == 0)
			continue;

		if (redcomp::LabelStorage::isLabel(line))
		{
//			if (halfInst)
//			{
//				PUSH_NOP();
//			}
//
//			labelStorage.insert(line, currentAddress);

			std::cerr << "Labels are not yet implemented" << std::endl;
			exit(-1);
		}
		else if (redcomp::Address::isAddress(line))
		{
			if (halfInst)
			{
				PUSH_NOP();
			}

			uint64_t newAddress = redcomp::Address::getAddress(line);
			segmentStorage.createNew(newAddress);
			currentAddress = newAddress;
		}
		else if (redcomp::AssemblyDirective::isAssemblyDirective(line))
		{
			auto result = redcomp::AssemblyDirective::parse(line);
			if (result.first)
			{
				segmentStorage.insert(result.second);
				currentAddress += result.second.size();
			}
		}
		else
		{
			// TODO implement LABEL parsing
			auto result = redcomp::Instruction::parse(line);
			if (result.first)
			{
				if (halfInst && result.second.size() == 4)
				{
					PUSH_NOP();
				}

				segmentStorage.insert(result.second);
				currentAddress += result.second.size();

				if (halfInst == false && result.second.size() == 2)
					halfInst = true;
				else
					halfInst = false;
			}
			else
			{
				std::cerr << "Error on line " << lineNo << std::endl;
				exit(-1);
			}
		}
	}

	if (halfInst)
	{
		PUSH_NOP();
	}

	// print segment table entry count
	print32(segmentStorage.segments.size());

	// print segment table entries
	for (size_t i = 0; i < segmentStorage.segments.size(); ++i)
	{
		// print segment start address 32-bits
		print32(segmentStorage.segments[i].first);

		// print segment length 32-bits
		print32(segmentStorage.segments[i].second.size());
	}

	// print segments
	for (size_t i = 0; i < segmentStorage.segments.size(); ++i)
	{
		for (size_t j = 0; j < segmentStorage.segments[i].second.size(); ++j)
		{
			printf("%c", segmentStorage.segments[i].second[j]);
		}
	}

	return 0;
}
