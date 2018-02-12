#include "redcomp/comp/utils.h"
#include "redcomp/comp/globals.h"

bool build_lookup_tables()
{
	// allocate tables
	opcode1_pack_table = malloc(256 * sizeof(enum InstructionPack));
	if (!opcode1_pack_table)
		return false;
	opcode1_template_table = malloc(256 * sizeof(enum InstructionTemplate));
	if (!opcode1_template_table)
		return false;

	// initialize tables
	for (size_t i = 0; i < 256; ++i)
	{
		if (i < instructionCount)
		{
			opcode1_pack_table[i] = instructions[i].pack;
			opcode1_template_table[i] = instructions[i]._template;
		}
		else
		{
			opcode1_pack_table[i] = IP_UNKNOWN;
			opcode1_template_table[i] = IT_UNKNOWN;
		}
	}
	return true;
}

bool fetch_next_inst()
{
	if (mem_read_16_big(pc, &fetched_inst))
	{
		pc += 2;
		return true;
	}
	else
		return false;
}

bool unpack_inst_params()
{
	fetched_inst_params.opcode1 = (fetched_inst >> 8) & 0xFF;
	fetched_inst_params.opcode2 = 0;
	fetched_inst_params.nfbits = 0;
	fetched_inst_params.instlen = 0;
	fetched_inst_params.stk1 = 0;
	fetched_inst_params.stk2 = 0;
	fetched_inst_params.idx1 = 0;
	fetched_inst_params.idx2 = 0;
	fetched_inst_params.reg = 0;
	fetched_inst_params.shfcnt = 0;
	fetched_inst_params.inccnt = 0;
	fetched_inst_params.integer = 0;
	fetched_inst_params.unsigned16 = 0;
	fetched_inst_params.signed16 = 0;
	fetched_inst_params.floating = 0.0;

	pack = opcode1_pack_table[fetched_inst_params.opcode1];
	if ((pack & IF_MG1C_FF00) == IF_MG1C_FF00)
		fetched_inst_params.opcode1 = (fetched_inst & 0xFF00) >> 8;
	if ((pack & IF_NBITS_00C0) == IF_NBITS_00C0)
		fetched_inst_params.nfbits = (fetched_inst & 0x00C0) >> 6;
	if ((pack & IF_ILEN_0030) == IF_ILEN_0030)
		fetched_inst_params.instlen = (fetched_inst & 0x0030) >> 4;
	if ((pack & IF_IX1_0030) == IF_IX1_0030)
		fetched_inst_params.idx1 = (fetched_inst & 0x0030) >> 4;
	if ((pack & IF_IX2_000C) == IF_IX2_000C)
		fetched_inst_params.idx2 = (fetched_inst & 0x000C) >> 2;
	if ((pack & IF_IX1_000C) == IF_IX1_000C)
		fetched_inst_params.idx1 = (fetched_inst & 0x000C) >> 2;
	if ((pack & IF_SX1_0003) == IF_SX1_0003)
		fetched_inst_params.stk1 = (fetched_inst & 0x0003);
	if ((pack & IF_SX1_000C) == IF_SX1_000C)
		fetched_inst_params.stk1 = (fetched_inst & 0x000C) >> 2;
	if ((pack & IF_SX2_0003) == IF_SX2_0003)
		fetched_inst_params.stk2 = (fetched_inst & 0x0003);
	if ((pack & IF_REG_003C) == IF_REG_003C)
		fetched_inst_params.reg = (fetched_inst & 0x003C) >> 2;
	if ((pack & IF_SHFCNT_003C) == IF_SHFCNT_003C)
		fetched_inst_params.shfcnt = (fetched_inst & 0x003C) >> 2;
	if ((pack & IF_INCCNT_003C) == IF_INCCNT_003C)
		fetched_inst_params.inccnt = (fetched_inst & 0x003C) >> 2;
	if ((pack & IF_INCCNT_000F) == IF_INCCNT_000F)
		fetched_inst_params.inccnt = (fetched_inst & 0x000F);

	_template = opcode1_template_table[fetched_inst_params.opcode1];
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
		fetched_inst_params.instlen = IL_1x16;
		break;
	case IT_NBITS__IX__B_VI_U16_B:
	case IT_NBITS__IX__B_IX_I16_B:
	case IT_NBITS__SX__B_VI_U16_B:
	case IT_NBITS__SX__B_IX_I16_B:
	case IT___PC_I16:
	case IT___IX_I16:
	case IT___B_VI_U16_B:
	case IT___B_IX_I16_B:
		fetched_inst_params.instlen = IL_2x16;
		break;
	default:
		return false;
	}
	return true;
}

bool fetch_opers()
{
	for (size_t i = 0; i < 8; ++i)
		fetched_opers[i] = 0;

	size_t byte_count;
	switch (fetched_inst_params.instlen)
	{
	case IL_1x16:
		byte_count = 0;
		break;
	case IL_2x16:
		byte_count = 2;
		break;
	case IL_3x16:
		byte_count = 4;
		break;
	case IL_5x16:
		byte_count = 8;
		break;
	default:
		return false;
	}

	for (size_t i = 0; i < 2; ++i)
	{
		int result = mem_read(pc++);
		if (result == -1)
			return false;
		fetched_opers[i] = result;
	}
	return true;
}
