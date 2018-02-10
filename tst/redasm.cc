#include "redcomp/Utils.hh"
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
	while (std::getline(std::cin, line))
	{
		++lineNo;

		std::cerr << "parsing:" << line << std::endl;
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
			labelStorage.insert(line, currentAddress);
		}
		else if (redcomp::Address::isAddress(line))
		{
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
			auto result = redcomp::Instruction::parse(line);
			if (result.first)
			{
				segmentStorage.insert(result.second);
				currentAddress += result.second.size();

				for (size_t i = 0; i < result.second.size(); ++i)
					printf("%c", result.second[i]);
			}
		}
	}

	return 0;
}
