#include "redcomp/comp/globals.h"



// Machine state
stk_t stk[4];
regs_t regs;
flags_t flags;

// Memory
page_table_t pt_lvl1;

// Internal state
struct InstructionParameters fetched_inst_params;
size_t skip_counter;

// Lookup tables
enum InstructionType *magic_to_type_table;
enum InstructionField *magic_to_fields_table;

