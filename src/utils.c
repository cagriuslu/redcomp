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
