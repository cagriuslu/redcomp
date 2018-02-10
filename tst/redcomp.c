#include "redcomp/comp/comp.h"
#include "redcomp/comp/mem.h"
#include <stdio.h>

#define MAC_OPERLEN (4)

comp_t comp;
mem_t *mem;
uint16_t inst;
uint16_t oper[MAC_OPERLEN];

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	mem = loadFromFile(stdin);
	if (mem == NULL)
		return -1;

	comp_init(&comp);

	while ((inst = mem_fetch_word(mem, &comp)) != 0)
	{
		printf("%04x ", inst);
	}
	printf("\n");

	return 0;
}