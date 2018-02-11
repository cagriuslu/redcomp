#pragma once

#include "redcomp/common/instruction.h"
#include "comp.h"
#include "mem.h"

extern enum InstructionPack *opcode1_pack_table;
int build_opcode1_pack_table();
extern enum InstructionTemplate *opcode1_template_table;
int build_opcode1_template_table();

void unpack_inst(uint16_t inst, enum InstructionPack pack, enum InstructionTemplate _template, struct InstructionParameters *params);
