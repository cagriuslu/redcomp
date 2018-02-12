#pragma once
#include "defs.h"
#include "redcomp/common/instruction.h"

// Machine state
extern stk_t sx[4];
extern uint64_t ix[4];
extern uint64_t pc;
extern uint64_t vi;
extern flags_t flags;

// Memory
extern page_table_t pt_lvl1;

// Internal state
extern uint16_t fetched_inst;
extern uint8_t fetched_opers[8];
extern size_t fetched_oper_count;
extern struct InstructionParameters fetched_inst_params;
extern enum InstructionPack pack;
extern enum InstructionTemplate _template;

// Lookup tables
extern enum InstructionPack *opcode1_pack_table;
extern enum InstructionTemplate *opcode1_template_table;
