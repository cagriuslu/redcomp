#pragma once
#include "comp.h"
#include "reg.h"
#include <stdio.h>
#include <stdlib.h>

#define MEMSEG_SIZE (65536)

typedef struct memseg
{
	uint8_t seg[MEMSEG_SIZE];
	uint64_t seg_addr;
} memseg_t;

void memseg_init(memseg_t *p);

typedef struct mem
{
	memseg_t *segs;
	size_t seg_count;
} mem_t;

mem_t* loadFromFile(FILE *f);
uint16_t mem_fetch_word(mem_t *mem, comp_t *comp)
{
	uint16_t inst = 0;
	inst |= mem->segs[0].seg[comp->pc++] << 8;
	inst |= mem->segs[0].seg[comp->pc++];
	return inst;
}
