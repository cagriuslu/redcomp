#include "redcomp/asm/Instruction.hh"

enum InstructionLength
{
	IL_1x16 = 0x0,
	IL_2x16 = 0x1,
	IL_3x16 = 0x2,
	IL_5x16 = 0x3,
};

enum InstructionField
{
	IF_MG1C_FF00   = 0x0001,
	IF_NBITS_00C0   = 0x0002,
	IF_ILEN_0030   = 0x0004,
	IF_IX1_0030    = 0x0008,
	IF_IX2_000C    = 0x0010,
	IF_IX1_000C    = 0x0020,
	IF_SX1_0003    = 0x0040,
	IF_SX1_000C    = 0x0080,
	IF_SX2_0003    = 0x0100,
	IF_REG_003C    = 0x0200,
	IF_SHFCNT_003C = 0x0400,
	IF_INCCNT_003C = 0x0800,
	IF_INCCNT_000F = 0x1000,
};

enum InstructionPack
{
	IP_UNKNOWN = 0,
	IP_MG1C8_NBITS2_INSTL2_IX2_Z2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_ILEN_0030 | IF_IX1_000C,
	IP_MG1C8_Z2_INSTL2_Z4 = IF_MG1C_FF00 | IF_ILEN_0030,
	IP_MG1C8_NBITS2_INSTL2_Z2_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_ILEN_0030 | IF_SX1_0003,
	IP_MG1C8_FBITS2_INSTL2_Z2_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_ILEN_0030 | IF_SX1_0003,
	IP_MG1C8_NBITS2_IX2_IX2_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_IX1_0030 | IF_IX2_000C | IF_SX1_0003,
	IP_MG1C8_NBITS2_IX2_SX2_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_IX1_0030 | IF_SX1_000C | IF_SX2_0003,
	IP_MG1C8_NBITS2_IX2_Z4 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_IX1_0030,
	IP_MG1C8_NBITS2_IX2_IX2_Z2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_IX1_0030 | IF_IX2_000C,
	IP_MG1C8_Z2_IX2_IX2_Z2 = IF_MG1C_FF00 | IF_IX1_0030 | IF_IX2_000C,
	IP_MG1C8_NBITS2_IX2_Z2_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_IX1_0030 | IF_SX1_0003,
	IP_MG1C8_NBITS2_Z4_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_SX1_0003,
	IP_MG1C8_FBITS2_Z4_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_SX1_0003,
	IP_MG1C8_NBITS2_Z2_SX2_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_SX1_000C | IF_SX2_0003,
	IP_MG1C8_NBITS2_REG4_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_SX1_0003 | IF_REG_003C,
	IP_MG1C8_Z8 = IF_MG1C_FF00,
	IP_MG1C8_NBITS2_SHFCNT4_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_SX1_0003 | IF_SHFCNT_003C,
	IP_MG1C8_NBITS2_INCCNT4_SX2 = IF_MG1C_FF00 | IF_NBITS_00C0 | IF_SX1_0003 | IF_INCCNT_003C,
	IP_MG1C8_Z2_IX2_INCCNT4 = IF_MG1C_FF00 | IF_IX1_0030 | IF_INCCNT_000F,
	IP_MG1C8_Z2_IX2_Z4 = IF_MG1C_FF00 | IF_IX1_0030,
	IP_MG1C8_Z2_IX2_Z2_SX2 = IF_MG1C_FF00 | IF_IX1_0030 | IF_SX1_0003,
	IP_MG1C8_NBITS2_Z6 = IF_MG1C_FF00 | IF_NBITS_00C0,
	IP_MG1C8_FBITS2_Z6 = IF_MG1C_FF00 | IF_NBITS_00C0,
	IP_MG1C8_Z4_INCCNT4 = IF_MG1C_FF00 | IF_INCCNT_000F,
	IP_MG1C8_Z6_SX2 = IF_MG1C_FF00 | IF_SX1_0003,
};

enum InstructionTemplate
{
	IT_UNKNOWN = 0,
	IT_NBITS__IX__INT,
	IT_NBITS__IX__GLABEL, // new
	IT_NBITS__IX__B_INT_B,
	IT_NBITS__IX__B_GLABEL_B, // new
	IT_NBITS__IX__B_VI_U16_B,
	IT_NBITS__IX__B_IX_B,
	IT_NBITS__IX__B_IX_I16_B,
	IT_NBITS__IX__B_IX_SX_B,
	IT_NBITS__IX,
	IT___IX__IX,
	IT_NBITS__IX__SX,
	IT_NBITS__SX__INT,
	IT_NBITS__SX__GLABEL, // new
	IT_FBITS__SX__FLOAT,
	IT_NBITS__SX__B_INT_B,
	IT_NBITS__SX__B_GLABEL_B, // new
	IT_NBITS__SX__B_VI_U16_B,
	IT_NBITS__SX__B_IX_B,
	IT_NBITS__SX__B_IX_I16_B,
	IT_NBITS__SX__B_IX_SX_B,
	IT_NBITS__SX__SX,
	IT_NBITS__SX__REG,
	IT___,
	IT_NBITS__SX,
	IT_FBITS__SX,
	IT_NBITS__SX__SHFCNT,
	IT_NBITS,
	IT_FBITS,
	IT_NBITS__SX__INCCNT,
	IT___IX__INCCNT,
	IT___INT,
	IT___GLABEL, // new
	IT___PC_I16,
	IT___PC_LLABEL, // new
	IT___IX,
	IT___IX_I16,
	IT___IX_SX,
	IT___B_INT_B,
	IT___B_GLABEL_B, // new
	IT___B_VI_U16_B,
	IT___B_IX_B,
	IT___B_IX_I16_B,
	IT___B_IX_SX_B,
	IT_NBITS__IX__IX,
	IT_NBITS__SX__IX,
	IT___INCCNT,
	IT___SX,
};

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

struct Instruction
{
	std::string mnemonic;
	InstructionPack pack;
	InstructionTemplate _template;
	uint8_t opcode1;
	uint8_t opcode2;
};

const Instruction instructions[] =
{
	{"load",     IP_MG1C8_NBITS2_INSTL2_IX2_Z2,  IT_NBITS__IX__INT,         0x01, 0x00},
	{"load",     IP_MG1C8_NBITS2_INSTL2_IX2_Z2,  IT_NBITS__IX__B_INT_B,     0x02, 0x00},
	{"load",     IP_MG1C8_NBITS2_IX2_Z4,         IT_NBITS__IX__B_VI_U16_B,  0x03, 0x00},
	{"load",     IP_MG1C8_NBITS2_IX2_IX2_Z2,    IT_NBITS__IX__B_IX_B,     0x04, 0x00},
	{"load",     IP_MG1C8_NBITS2_IX2_IX2_Z2,    IT_NBITS__IX__B_IX_I16_B, 0x05, 0x00},
	{"load",     IP_MG1C8_NBITS2_IX2_IX2_SX2,     IT_NBITS__IX__B_IX_SX_B, 0x06, 0x00},
	{"sign",     IP_MG1C8_NBITS2_IX2_Z4,         IT_NBITS__IX,              0x07, 0x00},
	{"add",      IP_MG1C8_Z2_IX2_IX2_Z2,     IT___IX__IX,              0x08, 0x00},
	{"add",      IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__IX__SX,         0x09, 0x00},
	{"push",     IP_MG1C8_NBITS2_INSTL2_Z2_SX2,  IT_NBITS__SX__INT,         0x0A, 0x00},
	{"push",     IP_MG1C8_FBITS2_INSTL2_Z2_SX2,  IT_FBITS__SX__FLOAT,       0x0B, 0x00},
	{"push",     IP_MG1C8_NBITS2_INSTL2_Z2_SX2,  IT_NBITS__SX__B_INT_B,     0x0C, 0x00},
	{"push",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX__B_VI_U16_B,  0x0D, 0x00},
	{"push",     IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__B_IX_B,     0x0E, 0x00},
	{"push",     IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__B_IX_I16_B, 0x0F, 0x00},
	{"push",     IP_MG1C8_NBITS2_IX2_IX2_SX2,     IT_NBITS__SX__B_IX_SX_B, 0x10, 0x00},
	{"push",     IP_MG1C8_NBITS2_Z2_SX2_SX2,    IT_NBITS__SX__SX,         0x11, 0x00},
	{"push",     IP_MG1C8_NBITS2_REG4_SX2,    IT_NBITS__SX__REG,         0x12, 0x00},
	{"pushall",  IP_MG1C8_Z8,                     IT___,                      0x13, 0x00},
	{"pop",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x14, 0x00},
	{"pop",      IP_MG1C8_NBITS2_INSTL2_Z2_SX2,  IT_NBITS__SX__B_INT_B,     0x15, 0x00},
	{"pop",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX__B_VI_U16_B,  0x16, 0x00},
	{"pop",      IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__B_IX_B,     0x17, 0x00},
	{"pop",      IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__B_IX_I16_B, 0x18, 0x00},
	{"pop",      IP_MG1C8_NBITS2_IX2_SX2_SX2,     IT_NBITS__SX__B_IX_SX_B, 0x19, 0x00},
	{"pop",      IP_MG1C8_NBITS2_REG4_SX2,    IT_NBITS__SX__REG,         0x1A, 0x00},
	{"popall",   IP_MG1C8_Z8,                     IT___,                      0x1B, 0x00},
	{"add",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x1C, 0x00},
	{"addc",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x1D, 0x00},
	{"add",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x1E, 0x00},
	{"addall",   IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x1F, 0x00},
	{"addallc",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x20, 0x00},
	{"addall",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x21, 0x00},
	{"sub",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x22, 0x00},
	{"subb",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x23, 0x00},
	{"sub",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x24, 0x00},
	{"suball",   IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x25, 0x00},
	{"suballb",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x26, 0x00},
	{"suball",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x27, 0x00},
	{"mulu",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x28, 0x00},
	{"muls",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x29, 0x00},
	{"mul",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x2A, 0x00},
	{"mulallu",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x2B, 0x00},
	{"mulalls",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x2C, 0x00},
	{"mulall",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x2D, 0x00},
	{"divu",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x2E, 0x00},
	{"divs",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x2F, 0x00},
	{"div",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x30, 0x00},
	{"divallu",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x31, 0x00},
	{"divalls",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x32, 0x00},
	{"divall",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x33, 0x00},
	{"modu",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x34, 0x00},
	{"mods",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x35, 0x00},
	{"and",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x36, 0x00},
	{"andall",   IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x37, 0x00},
	{"or",       IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x38, 0x00},
	{"orall",    IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x39, 0x00},
	{"xor",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x3A, 0x00},
	{"xorall",   IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x3B, 0x00},
	{"neg",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x3C, 0x00},
	{"neg",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x3D, 0x00},
	{"not",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x3E, 0x00},
	{"rotl",     IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x3F, 0x00},
	{"rotr",     IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x40, 0x00},
	{"rotlc",    IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x41, 0x00},
	{"rotrc",    IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x42, 0x00},
	{"shfl",     IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x43, 0x00},
	{"shfr",     IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x44, 0x00},
	{"shfe",     IP_MG1C8_NBITS2_SHFCNT4_SX2,       IT_NBITS__SX__SHFCNT,      0x45, 0x00},
	{"minu",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x46, 0x00},
	{"mins",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x47, 0x00},
	{"min",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x48, 0x00},
	{"minallu",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x49, 0x00},
	{"minalls",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x4A, 0x00},
	{"minall",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x4B, 0x00},
	{"maxu",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x4C, 0x00},
	{"maxs",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x4D, 0x00},
	{"max",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x4E, 0x00},
	{"maxallu",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x4F, 0x00},
	{"maxalls",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x50, 0x00},
	{"maxall",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x51, 0x00},
	{"avgu",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x52, 0x00},
	{"avgs",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x53, 0x00},
	{"avg",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x54, 0x00},
	{"avgallu",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x55, 0x00},
	{"avgalls",  IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x56, 0x00},
	{"avgall",   IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x57, 0x00},
	{"round",    IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x58, 0x00},
	{"ceil",     IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x59, 0x00},
	{"floor",    IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x5A, 0x00},
	{"sqrt",     IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x5B, 0x00},
	{"recip",    IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x5C, 0x00},
	{"abs",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x5D, 0x00},
	{"sin",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x5E, 0x00},
	{"cos",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x5F, 0x00},
	{"tan",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x60, 0x00},
	{"atan",     IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x61, 0x00},
	{"pow",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x62, 0x00},
	{"exp",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x63, 0x00},
	{"ln",       IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x64, 0x00},
	{"log",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x65, 0x00},
	{"pi",       IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x66, 0x00},
	{"endian",   IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x67, 0x00},
	{"float",    IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x68, 0x00},
	{"int",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x69, 0x00},
	{"float",    IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x6A, 0x00},
	{"sign",     IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x6B, 0x00},
	{"cmp",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x6C, 0x00},
	{"cmp",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x6D, 0x00},
	{"tst",      IP_MG1C8_NBITS2_Z4_SX2,         IT_NBITS__SX,              0x6E, 0x00},
	{"tst",      IP_MG1C8_FBITS2_Z4_SX2,         IT_FBITS__SX,              0x6F, 0x00},
	{"inc",      IP_MG1C8_NBITS2_INCCNT4_SX2,       IT_NBITS__SX__INCCNT,      0x70, 0x00},
	{"dec",      IP_MG1C8_NBITS2_INCCNT4_SX2,       IT_NBITS__SX__INCCNT,      0x71, 0x00},
	{"inc",      IP_MG1C8_Z2_IX2_INCCNT4,        IT___IX__INCCNT,           0x72, 0x00},
	{"dec",      IP_MG1C8_Z2_IX2_INCCNT4,        IT___IX__INCCNT,           0x73, 0x00},
	{"jmp",      IP_MG1C8_Z2_INSTL2_Z4,        IT___INT,                   0x74, 0x00},
	{"jmp",      IP_MG1C8_Z8,                     IT___PC_I16,                0x75, 0x00},
	{"jmp",      IP_MG1C8_Z2_IX2_Z4,          IT___IX,                   0x76, 0x00},
	{"jmp",      IP_MG1C8_Z2_IX2_Z4,          IT___IX_I16,               0x77, 0x00},
	{"jmp",      IP_MG1C8_Z2_IX2_Z2_SX2,     IT___IX_SX,               0x78, 0x00},
	{"skipc",    IP_MG1C8_Z8,                     IT___,                      0x79, 0x00},
	{"skipnc",   IP_MG1C8_Z8,                     IT___,                      0x7A, 0x00},
	{"skipz",    IP_MG1C8_Z8,                     IT___,                      0x7B, 0x00},
	{"skipnz",   IP_MG1C8_Z8,                     IT___,                      0x7C, 0x00},
	{"skipv",    IP_MG1C8_Z8,                     IT___,                      0x7D, 0x00},
	{"skipnv",   IP_MG1C8_Z8,                     IT___,                      0x7E, 0x00},
	{"skipn",    IP_MG1C8_Z8,                     IT___,                      0x7F, 0x00},
	{"skipnn",   IP_MG1C8_Z8,                     IT___,                      0x80, 0x00},
	{"skipp",    IP_MG1C8_Z8,                     IT___,                      0x81, 0x00},
	{"skipnp",   IP_MG1C8_Z8,                     IT___,                      0x82, 0x00},
	{"skipg",    IP_MG1C8_Z8,                     IT___,                      0x83, 0x00},
	{"skipng",   IP_MG1C8_Z8,                     IT___,                      0x84, 0x00},
	{"skipl",    IP_MG1C8_Z8,                     IT___,                      0x85, 0x00},
	{"skipnl",   IP_MG1C8_Z8,                     IT___,                      0x86, 0x00},
	{"call",     IP_MG1C8_Z2_INSTL2_Z4,        IT___INT,                   0x87, 0x00},
	{"call",     IP_MG1C8_Z8,                     IT___PC_I16,                0x88, 0x00},
	{"call",     IP_MG1C8_Z2_IX2_Z4,          IT___IX,                   0x89, 0x00},
	{"call",     IP_MG1C8_Z2_IX2_Z4,          IT___IX_I16,               0x8A, 0x00},
	{"call",     IP_MG1C8_Z2_IX2_Z2_SX2,     IT___IX_SX,               0x8B, 0x00},
	{"ret",      IP_MG1C8_Z8,                     IT___,                      0x8C, 0x00},
	{"syscall",  IP_MG1C8_Z8,                     IT___,                      0x8D, 0x00},
	{"retsys",   IP_MG1C8_Z8,                     IT___,                      0x8E, 0x00},
	{"setc",     IP_MG1C8_Z8,                     IT___,                      0x8F, 0x00},
	{"clrc",     IP_MG1C8_Z8,                     IT___,                      0x90, 0x00},
	{"up",       IP_MG1C8_Z2_INSTL2_Z4,        IT___B_INT_B,               0x91, 0x00},
	{"up",       IP_MG1C8_Z8,                     IT___B_VI_U16_B,            0x92, 0x00},
	{"up",       IP_MG1C8_Z2_IX2_Z4,          IT___B_IX_B,               0x93, 0x00},
	{"up",       IP_MG1C8_Z2_IX2_Z4,          IT___B_IX_I16_B,           0x94, 0x00},
	{"up",       IP_MG1C8_Z2_IX2_Z2_SX2,     IT___B_IX_SX_B,           0x95, 0x00},
	{"down",     IP_MG1C8_Z2_INSTL2_Z4,        IT___B_INT_B,               0x96, 0x00},
	{"down",     IP_MG1C8_Z8,                     IT___B_VI_U16_B,            0x97, 0x00},
	{"down",     IP_MG1C8_Z2_IX2_Z4,          IT___B_IX_B,               0x98, 0x00},
	{"down",     IP_MG1C8_Z2_IX2_Z4,          IT___B_IX_I16_B,           0x99, 0x00},
	{"down",     IP_MG1C8_Z2_IX2_Z2_SX2,     IT___B_IX_SX_B,           0x9A, 0x00},
	{"strdirp",  IP_MG1C8_Z8,                     IT___,                      0x9B, 0x00},
	{"strdirn",  IP_MG1C8_Z8,                     IT___,                      0x9C, 0x00},
	{"strcmp",   IP_MG1C8_NBITS2_IX2_IX2_Z2,    IT_NBITS__IX__IX,         0x9D, 0x00},
	{"strscan",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0x9E, 0x00},
	{"strcpy",   IP_MG1C8_NBITS2_IX2_IX2_Z2,    IT_NBITS__IX__IX,         0x9F, 0x00},
	{"strpush",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA0, 0x00},
	{"strpop",   IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA1, 0x00},
	{"inccmpz",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA2, 0x00},
	{"inccmpnz", IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA3, 0x00},
	{"inccmpg",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA4, 0x00},
	{"inccmpge", IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA5, 0x00},
	{"inccmpl",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA6, 0x00},
	{"inccmple", IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA7, 0x00},
	{"deccmpz",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA8, 0x00},
	{"deccmpnz", IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xA9, 0x00},
	{"deccmpg",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xAA, 0x00},
	{"deccmpge", IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xAB, 0x00},
	{"deccmpl",  IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xAC, 0x00},
	{"deccmple", IP_MG1C8_NBITS2_IX2_Z2_SX2,    IT_NBITS__SX__IX,         0xAD, 0x00},
	{"addm",     IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xAE, 0x00},
	{"addm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xAF, 0x00},
	{"addmm",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xB0, 0x00},
	{"addmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xB1, 0x00},
	{"subm",     IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xB2, 0x00},
	{"subm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xB3, 0x00},
	{"submm",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xB4, 0x00},
	{"submm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xB5, 0x00},
	{"mulmu",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xB6, 0x00},
	{"mulms",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xB7, 0x00},
	{"mulm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xB8, 0x00},
	{"mulmmu",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xB9, 0x00},
	{"mulmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xBA, 0x00},
	{"mulmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xBB, 0x00},
	{"divmu",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xBC, 0x00},
	{"divms",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xBD, 0x00},
	{"divm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xBE, 0x00},
	{"divmmu",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xBF, 0x00},
	{"divmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xC0, 0x00},
	{"divmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xC1, 0x00},
	{"modmu",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xC2, 0x00},
	{"modms",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xC3, 0x00},
	{"modmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xC4, 0x00},
	{"modmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xC5, 0x00},
	{"andm",     IP_MG1C8_Z8,                     IT___,                      0xC6, 0x00},
	{"andmm",    IP_MG1C8_Z8,                     IT___,                      0xC7, 0x00},
	{"orm",      IP_MG1C8_Z8,                     IT___,                      0xC8, 0x00},
	{"ormm",     IP_MG1C8_Z8,                     IT___,                      0xC9, 0x00},
	{"xorm",     IP_MG1C8_Z8,                     IT___,                      0xCA, 0x00},
	{"xormm",    IP_MG1C8_Z8,                     IT___,                      0xCB, 0x00},
	{"dotm",     IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xCC, 0x00},
	{"dotm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xCD, 0x00},
	{"dotmm",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xCE, 0x00},
	{"dotmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xCF, 0x00},
	{"minmu",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD0, 0x00},
	{"minms",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD1, 0x00},
	{"minm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xD2, 0x00},
	{"minmmu",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD3, 0x00},
	{"minmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD4, 0x00},
	{"minmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xD5, 0x00},
	{"maxmu",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD6, 0x00},
	{"maxms",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD7, 0x00},
	{"maxm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xD8, 0x00},
	{"maxmmu",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xD9, 0x00},
	{"maxmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xDA, 0x00},
	{"maxmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xDB, 0x00},
	{"avgmu",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xDC, 0x00},
	{"avgms",    IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xDD, 0x00},
	{"avgm",     IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xDE, 0x00},
	{"avgmmu",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xDF, 0x00},
	{"avgmms",   IP_MG1C8_NBITS2_Z6,              IT_NBITS,                   0xE0, 0x00},
	{"avgmm",    IP_MG1C8_FBITS2_Z6,              IT_FBITS,                   0xE1, 0x00},
	{"store",    IP_MG1C8_NBITS2_INSTL2_IX2_Z2,  IT_NBITS__IX__B_INT_B,     0xE2, 0x00},
	{"store",    IP_MG1C8_NBITS2_IX2_Z4,         IT_NBITS__IX__B_VI_U16_B,  0xE3, 0x00},
	{"store",    IP_MG1C8_NBITS2_IX2_IX2_Z2,    IT_NBITS__IX__B_IX_B,     0xE4, 0x00},
	{"store",    IP_MG1C8_NBITS2_IX2_IX2_Z2,    IT_NBITS__IX__B_IX_I16_B, 0xE5, 0x00},
	{"store",    IP_MG1C8_NBITS2_IX2_IX2_SX2,     IT_NBITS__IX__B_IX_SX_B, 0xE6, 0x00},
	{"rot",      IP_MG1C8_NBITS2_Z2_SX2_SX2,     IT_NBITS__SX__SX, 0xE7, 0x00},
	{"rotc",     IP_MG1C8_NBITS2_Z2_SX2_SX2,     IT_NBITS__SX__SX, 0xE8, 0x00},
	{"shf",      IP_MG1C8_NBITS2_Z2_SX2_SX2,     IT_NBITS__SX__SX, 0xE9, 0x00},
	{"shfe",     IP_MG1C8_NBITS2_Z2_SX2_SX2,     IT_NBITS__SX__SX, 0xEA, 0x00},
	{"pushvar",  IP_MG1C8_NBITS2_Z4_SX2,     IT_NBITS__SX, 0xEB, 0x00},
	{"popvar",   IP_MG1C8_NBITS2_Z4_SX2,     IT_NBITS__SX, 0xEC, 0x00},
	{"pushvar",  IP_MG1C8_NBITS2_IX2_Z4,     IT_NBITS__IX, 0xED, 0x00},
	{"popvar",   IP_MG1C8_NBITS2_IX2_Z4,     IT_NBITS__IX, 0xEE, 0x00},
	{"incvar",   IP_MG1C8_Z4_INCCNT4,     IT___INCCNT, 0xEF, 0x00},
	{"decvar",   IP_MG1C8_Z4_INCCNT4,     IT___INCCNT, 0xF0, 0x00},
	{"clr",      IP_MG1C8_Z2_IX2_Z4,     IT___IX, 0xF1, 0x00},
	{"clr",      IP_MG1C8_Z6_SX2,     IT___SX, 0xF2, 0x00},
	{"",         IP_UNKNOWN,          IT_UNKNOWN, 0, 0},
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
		if (instructions[i].mnemonic == mnemonic && instructions[i]._template == matchedTemplate)
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
