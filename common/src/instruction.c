#include "redcomp/common/instruction.h"

// This table has to be kept ordered with respect to magic
const struct Instruction instructions[] =
{
	{0x00, "nop", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x01, "trap", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x02, "pushv", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x03, "popv", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x04, "loadl", ITYP_WOPER, ITMP_MNE__S__IMM, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x05, "loadh", ITYP_WOPER, ITMP_MNE__S__IMM, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x06, "push", ITYP_WOPER, ITMP_MNE__S__B_R__IMM_B, IFLD_MAGIC_FF00 | IFLD_REG_00F0 | IFLD_SX1_00C0},
	{0x07, "push", ITYP_SHORT, ITMP_MNE__S__B_R__S_B, IFLD_MAGIC_FF00 | IFLD_REG_00F0 | IFLD_SX1_00C0 | IFLD_SX2_0003},
	{0x08, "push", ITYP_SHORT, ITMP_MNE__S__R, IFLD_MAGIC_FF00 | IFLD_REG_00F0 | IFLD_SX1_00C0},
	{0x09, "pop", ITYP_WOPER, ITMP_MNE__S__B_R__IMM_B, IFLD_MAGIC_FF00 | IFLD_REG_00F0 | IFLD_SX1_00C0},
	{0x0A, "pop", ITYP_SHORT, ITMP_MNE__S__B_R__S_B, IFLD_MAGIC_FF00 | IFLD_REG_00F0 | IFLD_SX1_00C0 | IFLD_SX2_0003},
	{0x0B, "pop", ITYP_SHORT, ITMP_MNE__S__R, IFLD_MAGIC_FF00 | IFLD_REG_00F0 | IFLD_SX1_00C0},
	{0x0C, "add", ITYP_WOPER, ITMP_MNE__S__IMM, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x0D, "add", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x0E, "and", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x0F, "or", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x10, "xor", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x11, "shfl", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x12, "shfr", ITYP_SHORT, ITMP_MNE__S, IFLD_MAGIC_FF00 | IFLD_SX1_00C0},
	{0x13, "skipc", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x14, "skipz", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x15, "skipv", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x16, "skipn", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x17, "setc", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
	{0x18, "clrc", ITYP_SHORT, ITMP_MNE, IFLD_MAGIC_FF00},
};

const size_t instructionCount = sizeof(instructions) / sizeof(struct Instruction);

void InstructionParametersInit(struct InstructionParameters *params)
{
	params->magic = 0;
	params->reg = 0;
	params->sx1 = 0;
	params->sx2 = 0;
	params->type = 0;
	params->operand = 0;
}
