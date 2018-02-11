#pragma once
#include <stdint.h>
#include <stdlib.h>

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

void flags_init(flags_t *p);
