#pragma once
#include "defs.h"
#include "redcomp/common/instruction.h"

// Machine state
extern stk_t stk[4];
extern regs_t regs;
extern flags_t flags;

// Memory
extern page_table_t pt_lvl1;

// Internal state
extern struct InstructionParameters fetched_inst_params;
extern size_t skip_counter; // skip if counter is 1

// Lookup tables
extern enum InstructionType *magic_to_type_table;
extern enum InstructionField *magic_to_fields_table;
