#include "redcomp/asm/Instruction.hh"

const std::string sl = "^";
const std::string mn = "([a-zA-Z]+)";
const std::string ws = "\\s+";
const std::string sx = "%(s[a-d])";
const std::string rg = "%(ia|ib|ic|id|vi|pc|zr|sr|ra|rb|rc|rd|re|rf|rg|rh)";
const std::string in = "([-+]?\\d+|[-+]?0[xX][\\da-fA-F]+|[-+]?0[bB][01]+)";
const std::string bo = "\\[";
const std::string bc = "\\]";
const std::string el = "$";

#define RGX_CONST (std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize)
const std::pair<InstructionTemplate, std::regex> instTempRegexes[] = {

	std::make_pair(ITMP_MNE,                std::regex(sl + mn                                         + el, RGX_CONST)),
	std::make_pair(ITMP_MNE__S__IMM,        std::regex(sl + mn + ws + sx + ws + in                     + el, RGX_CONST)),
	std::make_pair(ITMP_MNE__S__B_R__IMM_B, std::regex(sl + mn + ws + sx + ws + bo + rg + ws + in + bc + el, RGX_CONST)),
	std::make_pair(ITMP_MNE__S__B_R__S_B,   std::regex(sl + mn + ws + sx + ws + bo + rg + ws + sx + bc + el, RGX_CONST)),
	std::make_pair(ITMP_MNE__S__R,          std::regex(sl + mn + ws + sx + ws + rg                     + el, RGX_CONST)),
	std::make_pair(ITMP_MNE__S,             std::regex(sl + mn + ws + sx                               + el, RGX_CONST)),
	std::make_pair(ITMP_UNKNOWN,            std::regex("")),
};

uint8_t getStk(std::string s)
{
	uint8_t stk;

	if (s == "sa")
		stk = 0;
	else if (s == "sb")
		stk = 1;
	else if (s == "sc")
		stk = 2;
	else if (s == "sd")
		stk = 3;
	else
		stk = -1;

	return stk;
}

uint8_t getReg(std::string s)
{
	uint8_t reg;

	if (s == "ia")
		reg = 0;
	else if (s == "ib")
		reg = 1;
	else if (s == "ic")
		reg = 2;
	else if (s == "id")
		reg = 3;
	else if (s == "vi")
		reg = 4;
	else if (s == "pc")
		reg = 5;
	else if (s == "zr")
		reg = 6;
	else if (s == "sr")
		reg = 7;
	else if (s == "ra")
		reg = 8;
	else if (s == "rb")
		reg = 9;
	else if (s == "rc")
		reg = 10;
	else if (s == "rd")
		reg = 11;
	else if (s == "re")
		reg = 12;
	else if (s == "rf")
		reg = 13;
	else if (s == "rg")
		reg = 14;
	else if (s == "rh")
		reg = 15;
	else
		reg = -1;

	return reg;
}

uint16_t getU16(std::string s)
{
	return redcomp::Utils::strToU64(s);
}

struct InstructionParameters instructionParameters;

std::pair<bool,std::vector<uint8_t>> redcomp::Instruction::parse(std::string line)
{
	Utils::trimLeft(line);
	Utils::trimRight(line);
	if (line.length() == 0)
		return std::make_pair(false, std::vector<uint8_t>());

	int matchedTemplate = ITMP_UNKNOWN;
	std::smatch matches;
	for (size_t i = 0; instTempRegexes[i].first != ITMP_UNKNOWN; ++i)
	{
		if (std::regex_search(line, matches, instTempRegexes[i].second))
		{
			matchedTemplate = instTempRegexes[i].first;
			break;
		}
	}
	if (matchedTemplate == ITMP_UNKNOWN)
	{
		std::cerr << "No such instruction is found" << std::endl;
		return std::make_pair(false, std::vector<uint8_t>());
	}

//	for (size_t i = 0; i < matches.size(); ++i)
//	{
//		std::cerr << "[" << i << "]:" << matches[i].str() << std::endl;
//	}

	// check if the (mnemonic,template) pair exists
	int matchedInstIndex = -1;
	std::string mnemonic = matches[1].str();
	std::transform(mnemonic.begin(), mnemonic.end(), mnemonic.begin(), ::tolower);
	for (size_t i = 0; i < instructionCount; ++i)
	{
		if (std::string(instructions[i].mnemonic) == mnemonic && instructions[i].inst_template == matchedTemplate)
		{
			matchedInstIndex = i;
			break;
		}
	}
	if (matchedInstIndex == -1)
	{
		std::cerr << "No such mnemonic" << std::endl;
		return std::make_pair(false, std::vector<uint8_t>());
	}

	InstructionParametersInit(&instructionParameters);
	instructionParameters.magic = instructions[matchedInstIndex].magic;

#define M(idx) matches[idx].str()
	switch (matchedTemplate)
	{
	case ITMP_MNE:
		instructionParameters.type = ITYP_SHORT;
		break;
	case ITMP_MNE__S__IMM:
		instructionParameters.sx1 = getStk(M(2));
		instructionParameters.type = ITYP_WOPER;
		instructionParameters.operand = getU16(M(3));
		break;
	case ITMP_MNE__S__B_R__IMM_B:
		instructionParameters.sx1 = getStk(M(2));
		instructionParameters.reg = getReg(M(3));
		instructionParameters.type = ITYP_WOPER;
		instructionParameters.operand = getU16(M(4));
		break;
	case ITMP_MNE__S__B_R__S_B:
		instructionParameters.sx1 = getStk(M(2));
		instructionParameters.reg = getReg(M(3));
		instructionParameters.sx2 = getStk(M(4));
		instructionParameters.type = ITYP_SHORT;
		break;
	case ITMP_MNE__S__R:
		instructionParameters.sx1 = getStk(M(2));
		instructionParameters.reg = getReg(M(3));
		instructionParameters.type = ITYP_SHORT;
		break;
	case ITMP_MNE__S:
		instructionParameters.sx1 = getStk(M(2));
		instructionParameters.type = ITYP_SHORT;
		break;
	default:
		return std::make_pair(false, std::vector<uint8_t>());
	}
#undef M

	uint8_t inst[4] = {0, 0, 0, 0};
	int pack = instructions[matchedInstIndex].inst_fields;
	if (pack & IFLD_MAGIC_FF00)
		inst[0] |= instructionParameters.magic;
	if (pack & IFLD_REG_00F0)
		inst[1] |= instructionParameters.reg << 4;
	if (pack & IFLD_SX1_00C0)
		inst[1] |= instructionParameters.sx1 << 2;
	if (pack & IFLD_SX2_0003)
		inst[1] |= instructionParameters.sx2;

	if (instructionParameters.type == ITYP_WOPER)
	{
		inst[2] = instructionParameters.operand;
		inst[3] = instructionParameters.operand >> 8;
		return std::pair<bool,std::vector<uint8_t>>(true, {inst[0], inst[1], inst[2], inst[3]});
	}
	else
	{
		return std::pair<bool,std::vector<uint8_t>>(true, {inst[0], inst[1]});
	}
}
