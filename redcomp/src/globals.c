#include "redcomp/comp/globals.h"

stk_t sx[4];
uint64_t ix[4];
uint64_t pc;
uint64_t vi;
flags_t flags;

page_table_t pt_lvl1;

uint16_t fetched_inst;
uint8_t fetched_opers[8];
size_t fetched_oper_count;
struct InstructionParameters fetched_inst_params;
enum InstructionPack pack;
enum InstructionTemplate _template;

enum InstructionPack *opcode1_pack_table;
enum InstructionTemplate *opcode1_template_table;
