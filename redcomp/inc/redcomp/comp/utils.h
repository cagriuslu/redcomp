#pragma once
#include "redcomp/common/instruction.h"
#include "defs.h"
#include "flags.h"
#include "globals.h"
#include "mem.h"
#include "stk.h"

bool build_lookup_tables();
bool fetch_next_inst();

extern int (*do_funcs[])();
