#include "redcomp/asm/Instruction.hh"

const std::string sl = "^";
const std::string mn = "([a-eg-zA-EG-Z]+)";
const std::string nb = "(8|16|32|64)";
const std::string fb = "f(32|64)";
const std::string ws = "\\s+";
const std::string ix = "%(i[a-d])";
const std::string sx = "%(s[a-d])";
const std::string vi = "%(vi)";
const std::string pc = "%(pc)";
const std::string rg = "%(vi|pc)";
const std::string in = "([-+]?\\d+|[-+]?0[xX][\\da-fA-F]+|[-+]?0[bB][01]+)";
const std::string fl = "([-+]?\\d*\\.\\d+)";
const std::string sc = "s(1|2|3|4|5|6|7|8|12|16|20|24|32|40|48|56)";
const std::string ic = "i(1|2|4|8|16|32|64|128|256|512|1024|2048|4096|8192|16384|32768)";
const std::string bo = "\\[";
const std::string bc = "\\]";
const std::string el = "$";

#define RGX_CONST (std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize)
const std::pair<InstructionTemplate, std::regex> instTempRegexes[] = {
	std::make_pair(IT_NBITS__IX__INT,         std::regex(sl + mn + nb + ws + ix + ws      + in                + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__B_INT_B,     std::regex(sl + mn + nb + ws + ix + ws + bo + in           + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__B_VI_U16_B,  std::regex(sl + mn + nb + ws + ix + ws + bo + vi + ws + in + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__B_IX_B,     std::regex(sl + mn + nb + ws + ix + ws + bo + ix           + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__B_IX_I16_B, std::regex(sl + mn + nb + ws + ix + ws + bo + ix + ws + in + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__B_IX_SX_B, std::regex(sl + mn + nb + ws + ix + ws + bo + ix + ws + sx + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX,              std::regex(sl + mn + nb + ws + ix                               + el, RGX_CONST)),
	std::make_pair(IT___IX__IX,              std::regex(sl + mn      + ws + ix + ws      + ix                + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__SX,         std::regex(sl + mn + nb + ws + ix + ws      + sx                + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__INT,         std::regex(sl + mn + nb + ws + sx + ws      + in                + el, RGX_CONST)),
	std::make_pair(IT_FBITS__SX__FLOAT,       std::regex(sl + mn + fb + ws + sx + ws      + fl                + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__B_INT_B,     std::regex(sl + mn + nb + ws + sx + ws + bo + in           + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__B_VI_U16_B,  std::regex(sl + mn + nb + ws + sx + ws + bo + vi + ws + in + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__B_IX_B,     std::regex(sl + mn + nb + ws + sx + ws + bo + ix           + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__B_IX_I16_B, std::regex(sl + mn + nb + ws + sx + ws + bo + ix + ws + in + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__B_IX_SX_B, std::regex(sl + mn + nb + ws + sx + ws + bo + ix + ws + sx + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__SX,         std::regex(sl + mn + nb + ws + sx + ws      + sx                + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__REG,         std::regex(sl + mn + nb + ws + sx + ws      + rg                + el, RGX_CONST)),
	std::make_pair(IT___,                      std::regex(sl + mn                                              + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX,              std::regex(sl + mn + nb + ws + sx                               + el, RGX_CONST)),
	std::make_pair(IT_FBITS__SX,              std::regex(sl + mn + fb + ws + sx                               + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__SHFCNT,      std::regex(sl + mn + nb + ws + sx + ws      + sc                + el, RGX_CONST)),
	std::make_pair(IT_NBITS,                   std::regex(sl + mn + nb                                         + el, RGX_CONST)),
	std::make_pair(IT_FBITS,                   std::regex(sl + mn + fb                                         + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__INCCNT,      std::regex(sl + mn + nb + ws + sx + ws      + ic                + el, RGX_CONST)),
	std::make_pair(IT___IX__INCCNT,           std::regex(sl + mn      + ws + ix + ws      + ic                + el, RGX_CONST)),
	std::make_pair(IT___INT,                   std::regex(sl + mn      + ws + in                               + el, RGX_CONST)),
	std::make_pair(IT___PC_I16,                std::regex(sl + mn      + ws                + pc + ws + in      + el, RGX_CONST)),
	std::make_pair(IT___IX,                   std::regex(sl + mn      + ws + ix                               + el, RGX_CONST)),
	std::make_pair(IT___IX_I16,               std::regex(sl + mn      + ws                + ix + ws + in      + el, RGX_CONST)),
	std::make_pair(IT___IX_SX,               std::regex(sl + mn      + ws                + ix + ws + sx      + el, RGX_CONST)),
	std::make_pair(IT___B_INT_B,               std::regex(sl + mn      + ws           + bo + in           + bc + el, RGX_CONST)),
	std::make_pair(IT___B_VI_U16_B,            std::regex(sl + mn      + ws           + bo + vi + ws + in + bc + el, RGX_CONST)),
	std::make_pair(IT___B_IX_B,               std::regex(sl + mn      + ws           + bo + ix           + bc + el, RGX_CONST)),
	std::make_pair(IT___B_IX_I16_B,           std::regex(sl + mn      + ws           + bo + ix + ws + in + bc + el, RGX_CONST)),
	std::make_pair(IT___B_IX_SX_B,           std::regex(sl + mn      + ws           + bo + ix + ws + sx + bc + el, RGX_CONST)),
	std::make_pair(IT_NBITS__IX__IX,         std::regex(sl + mn + nb + ws + ix + ws      + ix                + el, RGX_CONST)),
	std::make_pair(IT_NBITS__SX__IX,         std::regex(sl + mn + nb + ws + sx + ws      + ix                + el, RGX_CONST)),
	std::make_pair(IT___INCCNT,                std::regex(sl + mn      + ws + ic                               + el, RGX_CONST)),
	std::make_pair(IT___SX,                   std::regex(sl + mn      + ws + sx                               + el, RGX_CONST)),
	std::make_pair(IT_UNKNOWN,                   std::regex("")),
};

uint8_t getNFBits(std::string s)
{
	if (s == "8")
		return 0;
	else if (s == "16")
		return 1;
	else if (s == "32")
		return 2;
	else if (s == "64")
		return 3;
	else
		return -1;
}

uint8_t getInstLen(uint64_t i)
{
	uint8_t *p = (uint8_t*) (&i);
	if (p[7] == 0 && p[6] == 0 && p[5] == 0 && p[4] == 0 && p[3] == 0 && p[2] == 0 && p[1] == 0 && p[0] == 0)
		return IL_1x16;
	else if (p[7] == 0 && p[6] == 0 && p[5] == 0 && p[4] == 0 && p[3] == 0 && p[2] == 0)
		return IL_2x16;
	else if (p[7] == 0 && p[6] == 0 && p[5] == 0 && p[4] == 0)
		return IL_3x16;
	else
		return IL_5x16;
}

uint8_t getFloatingInstLen(uint8_t nfbits)
{
	if (nfbits == 2)
		return 0;
	else if (nfbits == 3)
		return 1;
	else
		return -1;
}

uint8_t getStk(std::string s)
{
	if (s == "sa")
		return 0;
	else if (s == "sb")
		return 1;
	else if (s == "sc")
		return 2;
	else if (s == "sd")
		return 3;
	else
		return -1;
}

uint8_t getIdx(std::string s)
{
	if (s == "ia")
		return 0;
	else if (s == "ib")
		return 1;
	else if (s == "ic")
		return 2;
	else if (s == "id")
		return 3;
	else
		return -1;
}

uint8_t getReg(std::string s)
{
	if (s == "vi")
		return 0;
	else if (s == "pc")
		return 1;
	else
		return -1;
}

uint8_t getShfcnt(std::string s)
{
	if (s == "1")
		return 0;
	else if (s == "2")
		return 1;
	else if (s == "3")
		return 2;
	else if (s == "4")
		return 3;
	else if (s == "5")
		return 4;
	else if (s == "6")
		return 5;
	else if (s == "7")
		return 6;
	else if (s == "8")
		return 7;
	else if (s == "12")
		return 8;
	else if (s == "16")
		return 9;
	else if (s == "20")
		return 10;
	else if (s == "24")
		return 11;
	else if (s == "32")
		return 12;
	else if (s == "40")
		return 13;
	else if (s == "48")
		return 14;
	else if (s == "56")
		return 15;
	else
		return -1;
}

uint8_t getInccnt(std::string s)
{
	if (s == "1")
		return 0;
	else if (s == "2")
		return 1;
	else if (s == "4")
		return 2;
	else if (s == "8")
		return 3;
	else if (s == "16")
		return 4;
	else if (s == "32")
		return 5;
	else if (s == "64")
		return 6;
	else if (s == "128")
		return 7;
	else if (s == "256")
		return 8;
	else if (s == "512")
		return 9;
	else if (s == "1024")
		return 10;
	else if (s == "2048")
		return 11;
	else if (s == "4096")
		return 12;
	else if (s == "8192")
		return 13;
	else if (s == "16384")
		return 14;
	else if (s == "32768")
		return 15;
	else
		return -1;
}

uint16_t getU16(std::string s)
{
	int64_t n = redcomp::Utils::strToU64(s);
	if (n < std::numeric_limits<uint16_t>::min() || std::numeric_limits<uint16_t>::max() < n)
		std::cerr << s << " does not fit into unsigned 16-bit" << std::endl;
	return n;
}

int16_t getI16(std::string s)
{
	int64_t n = redcomp::Utils::strToU64(s);
	if (n < std::numeric_limits<int16_t>::min() || std::numeric_limits<int16_t>::max() < n)
		std::cerr << s << " does not fit into signed 16-bit" << std::endl;
	return n;
}

double getFloating(std::string s)
{
	return std::stod(s);
}

void fillRestArrayInteger(uint8_t *array, uint64_t integer)
{
	array[0] = (0xFF & integer);
	array[1] = (0xFF00 & integer) >> 8;
	array[2] = (0xFF0000 & integer) >> 16;
	array[3] = (0xFF000000 & integer) >> 24;
	array[4] = (0xFF00000000 & integer) >> 32;
	array[5] = (0xFF0000000000 & integer) >> 40;
	array[6] = (0xFF000000000000 & integer) >> 48;
	array[7] = (0xFF00000000000000 & integer) >> 56;
}

void fillRestArrayFloating(uint8_t *array, uint8_t instlen, double floating)
{
	uint8_t *ptr;
	float tmpFloat;

	switch (instlen)
	{
	case IL_3x16:
		tmpFloat = (float) floating;
		ptr = (uint8_t*) (&tmpFloat);
		array[0] = ptr[0];
		array[1] = ptr[1];
		array[2] = ptr[2];
		array[3] = ptr[3];
		return;
	case IL_5x16:
		ptr = (uint8_t*) (&floating);
		array[0] = ptr[0];
		array[1] = ptr[1];
		array[2] = ptr[2];
		array[3] = ptr[3];
		array[4] = ptr[4];
		array[5] = ptr[5];
		array[6] = ptr[6];
		array[7] = ptr[7];
		return;
	default:
		return;
	}
}

struct InstructionParameters
{
	uint8_t opcode1;
	uint8_t opcode2;
	uint8_t nfbits = 0;
	uint8_t instlen = 0;
	uint8_t stk1 = 0;
	uint8_t stk2 = 0;
	uint8_t idx1 = 0;
	uint8_t idx2 = 0;
	uint8_t reg = 0;
	uint8_t shfcnt = 0;
	uint8_t inccnt = 0;
	uint64_t integer = 0;
	uint16_t unsigned16 = 0;
	int16_t signed16 = 0;
	double floating = 0.0;
} instructionParameters;

std::pair<bool,std::vector<uint8_t>> redcomp::Instruction::parse(std::string line)
{
	Utils::trimLeft(line);
	Utils::trimRight(line);
	if (line.length() == 0)
		return std::make_pair(false, std::vector<uint8_t>());

	int matchedTemplate = IT_UNKNOWN;
	std::smatch matches;
	for (size_t i = 0; instTempRegexes[i].first != IT_UNKNOWN; ++i)
	{
		if (std::regex_search(line, matches, instTempRegexes[i].second))
		{
			matchedTemplate = instTempRegexes[i].first;
			break;
		}
	}
	if (matchedTemplate == IT_UNKNOWN)
	{
		std::cerr << "No such instruction is found" << std::endl;
		return std::make_pair(false, std::vector<uint8_t>());
	}

	for (size_t i = 0; i < matches.size(); ++i)
	{
		std::cerr << "[" << i << "]:" << matches[i].str() << std::endl;
	}

	// check if the (mnemonic,template) pair exists
	int matchedInstIndex = -1;
	std::string mnemonic = matches[1].str();
	for (size_t i = 0; instructions[i]._template != IT_UNKNOWN; ++i)
	{
		if (std::string(instructions[i].mnemonic) == mnemonic && instructions[i]._template == matchedTemplate)
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

	instructionParameters.opcode1 = instructions[matchedInstIndex].opcode1;
	instructionParameters.opcode2 = instructions[matchedInstIndex].opcode2;

#define M(idx) matches[idx].str()
	switch (matchedTemplate)
	{
	case IT_NBITS__IX__INT:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.integer = Utils::strToU64(M(4));
		instructionParameters.instlen = getInstLen(instructionParameters.integer);
		break;
	case IT_NBITS__IX__B_INT_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.integer = Utils::strToU64(M(4));
		instructionParameters.instlen = getInstLen(instructionParameters.integer);
		break;
	case IT_NBITS__IX__B_VI_U16_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.unsigned16 = getU16(M(5));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT_NBITS__IX__B_IX_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.idx2 = getIdx(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__IX__B_IX_I16_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.idx2 = getIdx(M(4));
		instructionParameters.signed16 = getI16(M(5));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT_NBITS__IX__B_IX_SX_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.idx2 = getIdx(M(4));
		instructionParameters.stk1 = getStk(M(5));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__IX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___IX__IX:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.idx2 = getIdx(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__IX__SX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.stk1 = getStk(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__INT:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.integer = Utils::strToU64(M(4));
		instructionParameters.instlen = getInstLen(instructionParameters.integer);
		break;
	case IT_FBITS__SX__FLOAT:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.floating = getFloating(M(4));
		instructionParameters.instlen = getFloatingInstLen(instructionParameters.nfbits);
		break;
	case IT_NBITS__SX__B_INT_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.integer = Utils::strToU64(M(4));
		instructionParameters.instlen = getInstLen(instructionParameters.integer);
		break;
	case IT_NBITS__SX__B_VI_U16_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.unsigned16 = getU16(M(5));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT_NBITS__SX__B_IX_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.idx1 = getIdx(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__B_IX_I16_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.idx1 = getIdx(M(4));
		instructionParameters.signed16 = getI16(M(5));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT_NBITS__SX__B_IX_SX_B:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.idx2 = getIdx(M(4));
		instructionParameters.stk2 = getStk(M(5));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__SX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.stk2 = getStk(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__REG:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.reg = getReg(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___:
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_FBITS__SX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__SHFCNT:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.shfcnt = getShfcnt(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_FBITS:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__INCCNT:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.inccnt = getInccnt(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___IX__INCCNT:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.inccnt = getInccnt(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___INT:
		instructionParameters.integer = Utils::strToU64(M(2));
		instructionParameters.instlen = getInstLen(instructionParameters.integer);
		break;
	case IT___PC_I16:
		instructionParameters.signed16 = getI16(M(3));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT___IX:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___IX_I16:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.signed16 = getI16(M(3));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT___IX_SX:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___B_INT_B:
		instructionParameters.integer = Utils::strToU64(M(2));
		instructionParameters.instlen = getInstLen(instructionParameters.integer);
		break;
	case IT___B_VI_U16_B:
		instructionParameters.unsigned16 = getU16(M(3));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT___B_IX_B:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___B_IX_I16_B:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.signed16 = getI16(M(3));
		instructionParameters.instlen = IL_2x16;
		break;
	case IT___B_IX_SX_B:
		instructionParameters.idx1 = getIdx(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__IX__IX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.idx1 = getIdx(M(3));
		instructionParameters.idx2 = getIdx(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT_NBITS__SX__IX:
		instructionParameters.nfbits = getNFBits(M(2));
		instructionParameters.stk1 = getStk(M(3));
		instructionParameters.idx1 = getIdx(M(4));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___INCCNT:
		instructionParameters.inccnt = getInccnt(M(2));
		instructionParameters.instlen = IL_1x16;
		break;
	case IT___SX:
		instructionParameters.stk1 = getStk(M(2));
		instructionParameters.instlen = IL_1x16;
		break;
	default:
		return std::make_pair(false, std::vector<uint8_t>());
	}
#undef M

	uint8_t first8[2] = {0, 0};
	uint8_t rest8[8] = {0,0,0,0};

	int pack = instructions[matchedInstIndex].pack;
	if (((int)pack & IF_MG1C_FF00) == IF_MG1C_FF00)
		first8[0] |= instructionParameters.opcode1;
	if (((int)pack & IF_NBITS_00C0) == IF_NBITS_00C0)
		first8[1] |= instructionParameters.nfbits << 6;
	if (((int)pack & IF_ILEN_0030) == IF_ILEN_0030)
		first8[1] |= instructionParameters.instlen << 4;
	if (((int)pack & IF_IX1_0030) == IF_IX1_0030)
		first8[1] |= instructionParameters.idx1 << 4;
	if (((int)pack & IF_IX2_000C) == IF_IX2_000C)
		first8[1] |= instructionParameters.idx2 << 2;
	if (((int)pack & IF_IX1_000C) == IF_IX1_000C)
		first8[1] |= instructionParameters.idx1 << 2;
	if (((int)pack & IF_SX1_0003) == IF_SX1_0003)
		first8[1] |= instructionParameters.stk1;
	if (((int)pack & IF_SX1_000C) == IF_SX1_000C)
		first8[1] |= instructionParameters.stk1 << 2;
	if (((int)pack & IF_SX2_0003) == IF_SX2_0003)
		first8[1] |= instructionParameters.stk2;
	if (((int)pack & IF_REG_003C) == IF_REG_003C)
		first8[1] |= instructionParameters.reg << 2;
	if (((int)pack & IF_SHFCNT_003C) == IF_SHFCNT_003C)
		first8[1] |= instructionParameters.shfcnt << 2;
	if (((int)pack & IF_INCCNT_003C) == IF_INCCNT_003C)
		first8[1] |= instructionParameters.inccnt << 2;
	if (((int)pack & IF_INCCNT_000F) == IF_INCCNT_000F)
		first8[1] |= instructionParameters.inccnt;

	switch (matchedTemplate)
	{
	case IT_NBITS__IX__INT:
	case IT_NBITS__IX__B_INT_B:
	case IT_NBITS__SX__INT:
	case IT_NBITS__SX__B_INT_B:
	case IT___INT:
	case IT___B_INT_B:
		fillRestArrayInteger(rest8, instructionParameters.integer);
		break;
	case IT_FBITS__SX__FLOAT:
		fillRestArrayFloating(rest8, instructionParameters.instlen, instructionParameters.floating);
		break;
	case IT_NBITS__IX__B_VI_U16_B:
	case IT_NBITS__SX__B_VI_U16_B:
	case IT___B_VI_U16_B:
		rest8[0] = instructionParameters.unsigned16 & 0xFF;
		rest8[1] = (instructionParameters.unsigned16 & 0xFF00) >> 8;
		break;
	case IT_NBITS__IX__B_IX_I16_B:
	case IT_NBITS__SX__B_IX_I16_B:
	case IT___PC_I16:
	case IT___IX_I16:
	case IT___B_IX_I16_B:
		rest8[0] = instructionParameters.signed16 & 0xFF;
		rest8[1] = (instructionParameters.signed16 & 0xFF00) >> 8;
		break;
	default:
		break;
	};

	switch (instructionParameters.instlen)
	{
	case IL_1x16:
		return std::pair<bool,std::vector<uint8_t>>(true, {first8[0], first8[1]});
	case IL_2x16:
		return std::pair<bool,std::vector<uint8_t>>(true, {first8[0], first8[1], rest8[0], rest8[1]});
	case IL_3x16:
		return std::pair<bool,std::vector<uint8_t>>(true, {first8[0], first8[1], rest8[0], rest8[1], rest8[2], rest8[3]});
	case IL_5x16:
		return std::pair<bool,std::vector<uint8_t>>(true, {first8[0], first8[1], rest8[0], rest8[1], rest8[2], rest8[3], rest8[4], rest8[5], rest8[6], rest8[7]});
	default:
		return std::pair<bool,std::vector<uint8_t>>(false, {});
	}
}
