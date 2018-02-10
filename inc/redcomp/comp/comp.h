#pragma once
#include "flags.h"
#include "reg.h"
#include "stk.h"
#include <stdint.h>
#include <stdlib.h>

#define STACK_COUNT (4)
#define INDEX_COUNT (4)

typedef struct comp
{
	stk_t sx[STACK_COUNT];
	reg_t ix[INDEX_COUNT];
	reg_t vi;
	reg_t pc;
	flags_t fl;
} comp_t;

void comp_init(comp_t *comp);
