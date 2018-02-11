#include "redcomp/comp/stk.h"

void stack_init(stk_t *p)
{
	for (size_t i = 0; i < STACK_SIZE; ++i)
		p->s[i] = 0;
	p->s_begin = 0;
	p->s_end = 0;
	p->s_size = 0;
};
