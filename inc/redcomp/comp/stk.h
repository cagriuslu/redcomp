#include <stdint.h>
#include <stdlib.h>

#define STACK_SIZE (32)

typedef struct stack
{
	uint8_t s[STACK_SIZE];
	size_t s_begin;
	size_t s_end;
	size_t s_size;
} stk_t;

void stack_init(stk_t *p);