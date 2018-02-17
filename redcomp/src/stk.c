#include "redcomp/comp/stk.h"
#include "redcomp/comp/globals.h"

uint32_t stk_pop(uint8_t sx)
{
	if (4 <= sx)
	{
		fprintf(stderr, "Implementation error\n");
		exit(-1);
	}

	if (stk[sx].s_top == 0)
		return 0;
	else
		return stk[sx].s[--stk[sx].s_top];
}

uint32_t stk_push(uint8_t sx, uint32_t value)
{
	if (4 <= sx)
	{
		fprintf(stderr, "Implementation error\n");
		exit(-1);
	}

	if (STACK_DEPTH == stk[sx].s_top)
	{
		// move everything one step down
		for (size_t i = 0; i < STACK_DEPTH - 1; ++i)
			stk[sx].s[i] = stk[sx].s[i+1];
		--stk[sx].s_top;
	}

	stk[sx].s[stk[sx].s_top++] = value;
	return value;
}
