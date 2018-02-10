#include "redcomp/common/instruction.h"

const struct Instruction instructions[] =
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
