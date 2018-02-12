#include "redcomp/common/instruction.h"
#include "redcomp/comp/globals.h"
#include "redcomp/comp/mem.h"
#include "redcomp/comp/utils.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	build_lookup_tables();

	// create the first page
	if (!mem_create(0))
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

	while (fetch_next_inst())
	{
		fprintf(stderr, "%04x ", fetched_inst);
		if (unpack_inst_params() == false || pack == IP_UNKNOWN || _template == IT_UNKNOWN)
		{
			fprintf(stderr, "Unknown instruction\n");
			exit(-1);
		}
		if (fetch_opers() == false)
		{
			fprintf(stderr, "Operand is not found\n");
			exit(-1);
		}

		// jump to execution do_ functions
	}

	return 0;
}