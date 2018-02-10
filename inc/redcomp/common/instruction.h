#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

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

struct Instruction
{
	char *mnemonic;
	enum InstructionPack pack;
	enum InstructionTemplate _template;
	uint8_t opcode1;
	uint8_t opcode2;
};

extern const struct Instruction instructions[];
extern const size_t instructionCount;

struct InstructionParameters
{
	uint8_t opcode1;
	uint8_t opcode2;
	uint8_t nfbits;
	uint8_t instlen;
	uint8_t stk1;
	uint8_t stk2;
	uint8_t idx1;
	uint8_t idx2;
	uint8_t reg;
	uint8_t shfcnt;
	uint8_t inccnt;
	uint64_t integer;
	uint16_t unsigned16;
	int16_t signed16;
	double floating;
};

#ifdef __cplusplus
}
#endif