#include "redcomp/comp/utils.h"

enum InstructionPack *opcode1_pack_table;

int build_opcode1_pack_table()
{
	opcode1_pack_table = malloc(256 * sizeof(enum InstructionPack));
	if (opcode1_pack_table == NULL)
		return -1;
	for (size_t i = 0; i < 256; ++i)
	{
		if (i < instructionCount)
			opcode1_pack_table[i] = instructions[i].pack;
		else
			opcode1_pack_table[i] = IP_UNKNOWN;
	}
	return 0;
}

enum InstructionTemplate *opcode1_template_table;

int build_opcode1_template_table()
{
	opcode1_template_table = malloc(256 * sizeof(enum InstructionTemplate));
	if (opcode1_template_table == NULL)
		return -1;
	for (size_t i = 0; i < 256; ++i)
	{
		if (i < instructionCount)
			opcode1_template_table[i] = instructions[i]._template;
		else
			opcode1_template_table[i] = IT_UNKNOWN;
	}
	return 0;
}

void unpack_inst(uint16_t inst, enum InstructionPack pack, enum InstructionTemplate _template, struct InstructionParameters *params)
{
	params->opcode1 = 0;
	params->opcode2 = 0;
	params->nfbits = 0;
	params->instlen = 0;
	params->stk1 = 0;
	params->stk2 = 0;
	params->idx1 = 0;
	params->idx2 = 0;
	params->reg = 0;
	params->shfcnt = 0;
	params->inccnt = 0;
	params->integer = 0;
	params->unsigned16 = 0;
	params->signed16 = 0;
	params->floating = 0.0;

	if ((pack & IF_MG1C_FF00) == IF_MG1C_FF00)
		params->opcode1 = (inst & 0xFF00) >> 8;
	if ((pack & IF_NBITS_00C0) == IF_NBITS_00C0)
		params->nfbits = (inst & 0x00C0) >> 6;
	if ((pack & IF_ILEN_0030) == IF_ILEN_0030)
		params->instlen = (inst & 0x0030) >> 4;
	if ((pack & IF_IX1_0030) == IF_IX1_0030)
		params->idx1 = (inst & 0x0030) >> 4;
	if ((pack & IF_IX2_000C) == IF_IX2_000C)
		params->idx2 = (inst & 0x000C) >> 2;
	if ((pack & IF_IX1_000C) == IF_IX1_000C)
		params->idx1 = (inst & 0x000C) >> 2;
	if ((pack & IF_SX1_0003) == IF_SX1_0003)
		params->stk1 = (inst & 0x0003);
	if ((pack & IF_SX1_000C) == IF_SX1_000C)
		params->stk1 = (inst & 0x000C) >> 2;
	if ((pack & IF_SX2_0003) == IF_SX2_0003)
		params->stk2 = (inst & 0x0003);
	if ((pack & IF_REG_003C) == IF_REG_003C)
		params->reg = (inst & 0x003C) >> 2;
	if ((pack & IF_SHFCNT_003C) == IF_SHFCNT_003C)
		params->shfcnt = (inst & 0x003C) >> 2;
	if ((pack & IF_INCCNT_003C) == IF_INCCNT_003C)
		params->inccnt = (inst & 0x003C) >> 2;
	if ((pack & IF_INCCNT_000F) == IF_INCCNT_000F)
		params->inccnt = (inst & 0x000F);

	switch (_template)
	{
	case IT_NBITS__IX__INT:
	case IT_NBITS__IX__B_INT_B:
	case IT_NBITS__SX__INT:
	case IT_FBITS__SX__FLOAT:
	case IT_NBITS__SX__B_INT_B:
	case IT___INT:
	case IT___B_INT_B:
		break;
	case IT_NBITS__IX__B_IX_B:
	case IT_NBITS__IX__B_IX_SX_B:
	case IT_NBITS__IX:
	case IT___IX__IX:
	case IT_NBITS__IX__SX:
	case IT_NBITS__SX__B_IX_B:
	case IT_NBITS__SX__B_IX_SX_B:
	case IT_NBITS__SX__SX:
	case IT_NBITS__SX__REG:
	case IT___:
	case IT_NBITS__SX:
	case IT_FBITS__SX:
	case IT_NBITS__SX__SHFCNT:
	case IT_NBITS:
	case IT_FBITS:
	case IT_NBITS__SX__INCCNT:
	case IT___IX__INCCNT:
	case IT___IX:
	case IT___IX_SX:
	case IT___B_IX_B:
	case IT___B_IX_SX_B:
	case IT_NBITS__IX__IX:
	case IT_NBITS__SX__IX:
	case IT___INCCNT:
	case IT___SX:
		params->instlen = IL_1x16;
		break;
	case IT_NBITS__IX__B_VI_U16_B:
	case IT_NBITS__IX__B_IX_I16_B:
	case IT_NBITS__SX__B_VI_U16_B:
	case IT_NBITS__SX__B_IX_I16_B:
	case IT___PC_I16:
	case IT___IX_I16:
	case IT___B_VI_U16_B:
	case IT___B_IX_I16_B:
		params->instlen = IL_2x16;
		break;
	default:
		params->instlen = IL_1x16;
	}
}
