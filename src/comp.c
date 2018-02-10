#include "redcomp/comp/comp.h"

comp_t comp;

void comp_init()
{
	for (size_t i = 0; i < STACK_COUNT; ++i)
		stack_init(comp.sx + i);
	for (size_t i = 0; i < INDEX_COUNT; ++i)
		reg_init(comp.ix + i);
	reg_init(&comp.vi);
	reg_init(&comp.pc);
	flags_init(&comp.fl);
}
