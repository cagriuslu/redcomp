#include "redcomp/asm/AssemblyDirective.hh"

// temp
#include <iostream>

#define RGX_CONST (std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize)

const std::regex asmdirLineIdentifier("^=", RGX_CONST);

bool redcomp::AssemblyDirective::isAssemblyDirective(std::string line)
{
	return std::regex_search(line, asmdirLineIdentifier);
}

enum AssemblyDirectiveType
{
	ASMDIR_NONE = 0,
	ASMDIR_WRITE_INT,
	ASMDIR_WRITE_MULTI_INT,
	ASMDIR_WRITE_FLOAT,
	ASMDIR_WRITE_MULTI_FLOAT,
	ASMDIR_WRITE_STRING,
	ASMDIR_WRITE_MULTI_STRING,
};

const std::pair<int,std::regex> asmdirRegexes[] =
{
	std::make_pair(ASMDIR_WRITE_INT,          std::regex("^=w(8|16|32|64)((\\s+[-+]?\\d+|\\s+[-+]?0[xX][\\da-fA-F]+|\\s+[-+]?0[bB][01]+)+)$", RGX_CONST)),
	std::make_pair(ASMDIR_WRITE_MULTI_INT,    std::regex("^=w(8|16|32|64)\\*(\\d+)((\\s+[-+]?\\d+|\\s+[-+]?0[xX][\\da-fA-F]+|\\s+[-+]?0[bB][01]+)+)$", RGX_CONST)),
	std::make_pair(ASMDIR_WRITE_FLOAT,        std::regex("^=wf(32|64)((\\s+[-+]?\\d*\\.\\d+)+)$", RGX_CONST)),
	std::make_pair(ASMDIR_WRITE_MULTI_FLOAT,  std::regex("^=wf(32|64)\\*(\\d+)((\\s+[-+]?\\d*\\.\\d+)+)$", RGX_CONST)),
	std::make_pair(ASMDIR_WRITE_STRING,       std::regex("^=ws\\s+(\\\".*\\\")$", RGX_CONST)),
	std::make_pair(ASMDIR_WRITE_MULTI_STRING, std::regex("^=ws\\*(\\d+)\\s+(\\\".*\\\")$", RGX_CONST)),
	std::make_pair(ASMDIR_NONE,               std::regex("")),
};

std::pair<bool,std::vector<uint8_t>> redcomp::AssemblyDirective::parse(std::string line)
{
	if (isAssemblyDirective(line) == false)
		return make_pair(false, std::vector<uint8_t>());

	int matchedDirective = ASMDIR_NONE;
	std::smatch matches;
	for (size_t i = 0; asmdirRegexes[i].first != ASMDIR_NONE; ++i)
	{
		if (std::regex_search(line, matches, asmdirRegexes[i].second))
		{
			matchedDirective = asmdirRegexes[i].first;
			break;
		}
	}

	if (matchedDirective == ASMDIR_NONE)
		return make_pair(false, std::vector<uint8_t>());

	for (size_t i = 0; i < matches.size(); ++i)
	{
		std::cerr << "[" << i << "]:" << matches[i].str() << std::endl;
	}

	switch (matchedDirective)
	{
	case ASMDIR_WRITE_INT:
		// TODO
	case ASMDIR_WRITE_MULTI_INT:
		// TODO
	case ASMDIR_WRITE_FLOAT:
		// TODO
	case ASMDIR_WRITE_MULTI_FLOAT:
		// TODO
	case ASMDIR_WRITE_STRING:
		// TODO
	case ASMDIR_WRITE_MULTI_STRING:
		// TODO
	default:
		return make_pair(false, std::vector<uint8_t>());
	}
}



