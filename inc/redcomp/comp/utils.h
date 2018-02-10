#pragma once

#include "../common/instruction.h"

extern enum InstructionPack *opcode1_pack_table;
int build_opcode1_pack_table();

void unpack_inst(uint16_t inst, enum InstructionPack pack, struct InstructionParameters *params);
