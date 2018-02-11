#include "redcomp/comp/comp.h"
#include "redcomp/comp/mem.h"
#include "redcomp/comp/utils.h"
#include "redcomp/common/instruction.h"
#include <stdio.h>

uint16_t inst;
uint8_t oper[8];
struct InstructionParameters instParams;

bool fetchOper()
{
	int result;
	size_t i;

	for (i = 0; i < 8; ++i)
		oper[i] = 0;

	switch (instParams.instlen)
	{
	case IL_1x16:
		return true;
	case IL_2x16:
		for (i = 0; i < 2; ++i)
		{
			result = mem_read(comp.pc++);
			if (result == -1)
				return false;
			oper[i] = result;
		}
		return true;
	case IL_3x16:
		for (i = 0; i < 4; ++i)
		{
			result = mem_read(comp.pc++);
			if (result == -1)
				return false;
			oper[i] = result;
		}
		return true;
	case IL_5x16:
		for (i = 0; i < 8; ++i)
		{
			result = mem_read(comp.pc++);
			if (result == -1)
				return false;
			oper[i] = result;
		}
		return true;
	default:
		return false;
	}
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	comp_init();
	build_opcode1_pack_table();
	build_opcode1_template_table();
	mem_init();
	if (mem_create(0) == NULL)
		return -1;

	// load first 65536 bytes of input
	fprintf(stderr, "Loading file...\n");
	size_t count = 0;
	int c;
	while ((c = getc(stdin)) != EOF && count < 65536)
	{
		fprintf(stderr, "%02x ", c);
		mem_write(count++, c);
	}
	fprintf(stderr, "\n");

	//mem_dump(0);

	while (mem_read_inst(comp.pc, &inst))
	{
		comp.pc += 2;
		fprintf(stderr, "%04x ", inst);
		uint8_t opcode1 = (inst >> 8) & 0xFF;
		enum InstructionPack pack = opcode1_pack_table[opcode1];
		enum InstructionTemplate _template = opcode1_template_table[opcode1];
		if (pack == IP_UNKNOWN || _template == IT_UNKNOWN)
		{
			fprintf(stderr, "Unknown instruction\n");
			exit(-1);
		}
		unpack_inst(inst, pack, _template, &instParams);
		if (fetchOper() == false)
		{
			fprintf(stderr, "Operand is not found\n");
			exit(-1);
		}

		// jump to execution function do_
	}
	fprintf(stderr, "\n");

	return 0;
}