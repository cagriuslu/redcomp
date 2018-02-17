#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACK_DEPTH (8)
typedef struct stack
{
	uint32_t s[STACK_DEPTH];
	uint8_t s_top; // points to the next empty space on stack
} stk_t;

typedef struct regs
{
	uint32_t ia;
	uint32_t ib;
	uint32_t ic;
	uint32_t id;
	uint32_t vi;
	uint32_t pc;
	uint32_t zr;
	uint32_t sr;
	uint32_t ra;
	uint32_t rb;
	uint32_t rc;
	uint32_t rd;
	uint32_t re;
	uint32_t rf;
	uint32_t rg;
	uint32_t rh;
} regs_t;

typedef struct flags
{
	uint8_t carry : 1;
	uint8_t zero : 1;
	uint8_t overflow : 1;
	uint8_t negative : 1;
} flags_t;

typedef struct page
{
	uint8_t buffer[65536];
} page_t;

typedef struct page_table
{
	union
	{
		struct page_table *child_table;
		struct page *page;
	} entry[65536];
} page_table_t;
