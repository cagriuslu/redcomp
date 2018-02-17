#include "redcomp/comp/utils.h"
#include "redcomp/comp/globals.h"

#define REG(r) (((uint32_t*)(&regs))[r])

bool build_lookup_tables()
{
	// allocate tables
	magic_to_type_table = malloc(256 * sizeof(enum InstructionType));
	if (!magic_to_type_table)
		return false;
	magic_to_fields_table = malloc(256 * sizeof(enum InstructionField));
	if (!magic_to_fields_table)
		return false;

	// initialize tables
	for (size_t i = 0; i < 256; ++i)
	{
		if (i < instructionCount)
		{
			magic_to_type_table[i] = instructions[i].inst_type;
			magic_to_fields_table[i] = instructions[i].inst_fields;
		}
		else
		{
			magic_to_type_table[i] = ITYP_UNKNOWN;
			magic_to_fields_table[i] = IFLD_UNKNOWN;
		}
	}
	return true;
}

bool fetch_next_inst()
{
	InstructionParametersInit(&fetched_inst_params);

	uint16_t inst;
	if (mem_read_16_big(regs.pc, &inst))
	{
		regs.pc += 2;

		// unpack instruction
		fetched_inst_params.magic = (inst >> 8) & 0xFF;
		int fields = magic_to_fields_table[fetched_inst_params.magic];
		if (fields & IFLD_REG_00F0)
			fetched_inst_params.reg = (inst >> 4) & 0xF;
		if (fields & IFLD_SX1_00C0)
			fetched_inst_params.sx1 = (inst >> 2) & 0x3;
		if (fields & IFLD_SX2_0003)
			fetched_inst_params.sx2 = inst & 0x3;
		fetched_inst_params.type = magic_to_type_table[fetched_inst_params.magic];
		if (fetched_inst_params.type == ITYP_WOPER)
		{
			if (mem_read_16_little(regs.pc, &fetched_inst_params.operand))
				regs.pc += 2;
			else
				return false;
		}

		return true;
	}
	else
		return false;
}

int do_nop()
{
	return 0;
}
int do_trap()
{
	// TODO
	return 0;
}
int do_pushv_sx()
{
	// decrement vi
	regs.vi -= 4;
	// pop from stack and write to vi
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	if (mem_write_32_little(regs.vi, value) == false)
		return -1;

	flags_update(value);

	return 0;
}
int do_popv_sx()
{
	// read from vi
	uint32_t value;
	if (mem_read_32_little(regs.vi, &value) == false)
		return -1;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);
	// increment vi
	regs.vi += 4;

	flags_update(value);

	return 0;
}
int do_loadl_sx_imm()
{
	// pop from stack
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// load
	value = (value & 0xFFFF0000) | fetched_inst_params.operand;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_loadh_sx_imm()
{
	// pop from stack
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// load
	value = (value & 0x0000FFFF) | (((uint32_t)fetched_inst_params.operand) << 16);
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_push_sx_reg_imm()
{
	// calculate address
	int32_t offset = ((int16_t)fetched_inst_params.operand);
	flags_check_add(REG(fetched_inst_params.reg), offset);
	uint32_t address = REG(fetched_inst_params.reg) + offset;
	// get value
	uint32_t value;
	if (mem_read_32_little(address, &value) == false)
		return -1;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_push_sx_reg_sx()
{
	// calculate address
	int32_t offset = stk_pop(fetched_inst_params.sx2); stk_push(fetched_inst_params.sx2, offset);
	flags_check_add(REG(fetched_inst_params.reg), offset);
	uint32_t address = REG(fetched_inst_params.reg) + offset;
	// get value
	uint32_t value;
	if (mem_read_32_little(address, &value) == false)
		return -1;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_push_sx_reg()
{
	// get value
	uint32_t value = REG(fetched_inst_params.reg);
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_pop_sx_reg_imm()
{
	// calculate address
	int32_t offset = ((int16_t)fetched_inst_params.operand);
	flags_check_add(REG(fetched_inst_params.reg), offset);
	uint32_t address = REG(fetched_inst_params.reg) + offset;
	// get value
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// write value
	if (mem_write_32_little(address, value) == false)
		return -1;

	flags_update(value);

	return 0;
}
int do_pop_sx_reg_sx()
{
	// calculate address
	int32_t offset = stk_pop(fetched_inst_params.sx2); stk_push(fetched_inst_params.sx2, offset);
	flags_check_add(REG(fetched_inst_params.reg), offset);
	uint32_t address = REG(fetched_inst_params.reg) + offset;
	// get value
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// write value
	if (mem_write_32_little(address, value) == false)
		return -1;

	flags_update(value);

	return 0;
}
int do_pop_sx_reg()
{
	// get value
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// write to register
	REG(fetched_inst_params.reg) = value;

	flags_update(value);

	return 0;
}
int do_add_sx_imm()
{
	// get current value
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// get offset
	int32_t offset = ((int16_t)fetched_inst_params.operand);
	// calc new value
	flags_check_add(value, offset);
	value += offset;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_add_sx()
{
	// get current values
	uint32_t value1 = stk_pop(fetched_inst_params.sx1);
	uint32_t value2 = stk_pop(fetched_inst_params.sx1);
	// calc new value
	flags_check_add(value1, value2);
	uint32_t value = value1 + value2;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_and_sx()
{
	// get current values
	uint32_t value1 = stk_pop(fetched_inst_params.sx1);
	uint32_t value2 = stk_pop(fetched_inst_params.sx1);
	// calc new value
	uint32_t value = value1 & value2;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_or_sx()
{
	// get current values
	uint32_t value1 = stk_pop(fetched_inst_params.sx1);
	uint32_t value2 = stk_pop(fetched_inst_params.sx1);
	// calc new value
	uint32_t value = value1 | value2;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_xor_sx()
{
	// get current values
	uint32_t value1 = stk_pop(fetched_inst_params.sx1);
	uint32_t value2 = stk_pop(fetched_inst_params.sx1);
	// calc new value
	uint32_t value = value1 ^ value2;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_shfl_sx()
{
	// get current value
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// calc
	uint32_t tmp_carry = value & 0x80000000;
	value <<= 1;
	value &= 0xFFFFFFFE;
	if (flags.carry)
		value |= 0x1;
	// set carry
	if (tmp_carry)
		flags.carry = 1;
	else
		flags.carry = 0;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_shfr_sx()
{
	// get current value
	uint32_t value = stk_pop(fetched_inst_params.sx1);
	// calc
	uint32_t tmp_carry = value & 0x1;
	value >>= 1;
	value &= 0x7FFFFFFF;
	if (flags.carry)
		value |= 0x80000000;
	// set carry
	if (tmp_carry)
		flags.carry = 1;
	else
		flags.carry = 0;
	// push to stack
	stk_push(fetched_inst_params.sx1, value);

	flags_update(value);

	return 0;
}
int do_skipC()
{
	if (flags.carry)
		skip_counter = 1;
	else
		skip_counter = 2;
	return 0;
}
int do_skipZ()
{
	if (flags.zero)
		skip_counter = 1;
	else
		skip_counter = 2;
	return 0;
}
int do_skipV()
{
	if (flags.overflow)
		skip_counter = 1;
	else
		skip_counter = 2;
	return 0;
}
int do_skipN()
{
	if (flags.negative)
		skip_counter = 1;
	else
		skip_counter = 2;
	return 0;
}
int do_setc()
{
	flags.carry = 1;
	return 0;
}
int do_clrc()
{
	flags.carry = 0;
	return 0;
}

int (*do_funcs[])() =
{
	do_nop,
	do_trap,
	do_pushv_sx,
	do_popv_sx,
	do_loadl_sx_imm,
	do_loadh_sx_imm,
	do_push_sx_reg_imm,
	do_push_sx_reg_sx,
	do_push_sx_reg,
	do_pop_sx_reg_imm,
	do_pop_sx_reg_sx,
	do_pop_sx_reg,
	do_add_sx_imm,
	do_add_sx,
	do_and_sx,
	do_or_sx,
	do_xor_sx,
	do_shfl_sx,
	do_shfr_sx,
	do_skipC,
	do_skipZ,
	do_skipV,
	do_skipN,
	do_setc,
	do_clrc,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};
