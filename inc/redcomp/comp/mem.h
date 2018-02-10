#pragma once
#include "comp.h"
#include "reg.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct seg
{
	uint8_t buf[65536];
} seg_t;

typedef struct seg_tab
{
	union
	{
		struct seg_tab *tab;
		struct seg *seg;
	} entry[65536];
} seg_tab_t;

extern seg_tab_t seg_tab_lvl1;

void mem_init();
seg_t* mem_check(uint64_t addr);
seg_t* mem_create(uint64_t addr);
void mem_destroy(uint64_t addr);
int mem_read(uint64_t addr);
int mem_read_ex(seg_t *seg, uint64_t addr);
int mem_write(uint64_t addr, uint8_t val);
bool mem_dump(uint64_t addr);

bool mem_read_inst(uint64_t addr, uint16_t *out);
