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

void unpack_inst(uint16_t inst, enum InstructionPack pack, struct InstructionParameters *params)
{
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
}
