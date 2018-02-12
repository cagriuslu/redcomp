#pragma once
#include "redcomp/common/instruction.h"
#include "defs.h"
#include "flags.h"
#include "globals.h"
#include "mem.h"

bool build_lookup_tables();
bool fetch_next_inst();
bool unpack_inst_params();
bool fetch_opers();
