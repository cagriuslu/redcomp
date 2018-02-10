#include "redcomp/comp/flags.h"

void flags_init(flags_t *p)
{
	p->carry = 0;
	p->zero = 0;
	p->overflow = 0;
	p->strdir = 0;
	p->sign = 0;
	p->parity = 0;
	p->less = 0;
	p->greater = 0;
}
