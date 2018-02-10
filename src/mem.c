#include "redcomp/comp/mem.h"

void memseg_init(memseg_t *p)
{
	for (size_t i = 0; i < MEMSEG_SIZE; ++i)
		p->seg[i] = 0;
	p->seg_addr = 0;
}

mem_t* loadFromFile(FILE *f)
{
	mem_t *mem = malloc(sizeof(mem_t));
	if (mem == NULL)
		return NULL;

	// create one segment
	mem->segs = malloc(sizeof(memseg_t));
	if (mem->segs == NULL)
		return NULL;
	mem->seg_count = 1;
	memseg_init(mem->segs);

	size_t count = 0;
	int c;
	while ((c = getc(f)) != EOF && count < MEMSEG_SIZE)
	{
		mem->segs[0].seg[count++] = c;
	}

	return mem;
}
