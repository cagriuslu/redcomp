#include "redcomp/comp/flags.h"
#include "redcomp/comp/globals.h"

void flags_init()
{
	flags.carry = 0;
	flags.zero = 0;
	flags.overflow = 0;
	flags.strdir = 0;
	flags.sign = 0;
	flags.parity = 0;
	flags.less = 0;
	flags.greater = 0;
}
