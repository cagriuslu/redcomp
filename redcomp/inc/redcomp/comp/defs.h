#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stack
{
	uint8_t s[32];
	size_t s_begin;
	size_t s_end;
	size_t s_size;
} stk_t;

typedef struct flags
{
	uint8_t carry : 1;
	uint8_t zero : 1;
	uint8_t overflow : 1;
	uint8_t strdir : 1;
	uint8_t sign : 1;
	uint8_t parity : 1;
	uint8_t less : 1;
	uint8_t greater : 1;
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
