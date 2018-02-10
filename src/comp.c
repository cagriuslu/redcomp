#include "redcomp/comp/comp.h"

void comp_init(comp_t *p)
{
	for (size_t i = 0; i < STACK_COUNT; ++i)
		stack_init(p->sx + i);
	for (size_t i = 0; i < INDEX_COUNT; ++i)
		reg_init(p->ix + i);
	reg_init(&p->vi);
	reg_init(&p->pc);
	flags_init(&p->fl);
}
