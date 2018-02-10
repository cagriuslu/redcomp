#include "redcomp/comp/comp.h"
#include "redcomp/comp/mem.h"
#include "redcomp/comp/utils.h"
#include "redcomp/common/instruction.h"
#include <stdio.h>

#define MAC_OPERLEN (4)

uint16_t inst;
uint16_t oper[MAC_OPERLEN];
struct InstructionParameters instParams;

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	comp_init();
	build_opcode1_pack_table();
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
		if (pack == IP_UNKNOWN)
		{
			fprintf(stderr, "Unknown instruction\n");
			exit(-1);
		}
		unpack_inst(inst, pack, &instParams);
	}
	fprintf(stderr, "\n");

	return 0;
}