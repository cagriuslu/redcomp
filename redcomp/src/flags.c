#include "redcomp/comp/flags.h"
#include "redcomp/comp/globals.h"

void flags_init()
{
	flags.carry = 0;
	flags.zero = 0;
	flags.overflow = 0;
	flags.negative = 0;
}

void flags_update(uint32_t value)
{
	if (value == 0)
		flags.zero = 1;
	else
		flags.zero = 0;

	if (value & 0x80000000)
		flags.negative = 1;
	else
		flags.negative = 0;
}

void flags_check_add(uint32_t n1, uint32_t n2)
{
	uint32_t max = (n1 < n2) ? n2 : n1;
	if (n1 + n2 < max)
		flags.carry = 1;
	else
		flags.carry = 0;

	if (((n1 & 0x80000000) == (n2 & 0x80000000)) && ((n1 & 0x80000000) != ((n1+n2) & 0x80000000)))
		flags.overflow = 1;
	else
		flags.overflow = 0;
}
