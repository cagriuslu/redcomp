#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

enum InstructionType
{
	ITYP_UNKNOWN = 0,
	ITYP_SHORT,
	ITYP_WOPER,
};

enum InstructionTemplate
{
	ITMP_UNKNOWN = 0,
	ITMP_MNE,
	ITMP_MNE__S__IMM,
	ITMP_MNE__S__B_R__IMM_B,
	ITMP_MNE__S__B_R__S_B,
	ITMP_MNE__S__R,
	ITMP_MNE__S,
};

enum InstructionField
{
	IFLD_UNKNOWN = 0,
	IFLD_MAGIC_FF00 = 1,
	IFLD_REG_00F0 = 2,
	IFLD_SX1_00C0 = 4,
	IFLD_SX2_0003 = 8,
};

struct Instruction
{
	uint8_t magic;
	char* mnemonic;
	int inst_type;
	int inst_template;
	int inst_fields;
};

extern const struct Instruction instructions[];
extern const size_t instructionCount;

struct InstructionParameters
{
	uint8_t magic;
	uint8_t reg;
	uint8_t sx1;
	uint8_t sx2;
	int type;
	uint16_t operand;
};
void InstructionParametersInit(struct InstructionParameters *params);

#ifdef __cplusplus
}
#endif
