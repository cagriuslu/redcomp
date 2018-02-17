#include "redcomp/common/instruction.h"
#include "redcomp/comp/globals.h"
#include "redcomp/comp/mem.h"
#include "redcomp/comp/utils.h"
#include <stdio.h>

bool scan32(uint32_t *out)
{
	uint32_t n = 0;
	int c;
	for (size_t i = 0; i < 4; ++i)
	{
		c = getc(stdin);
		if (c == EOF)
			return false;
		else
			n |= c << (8*i);
	}
	if (out)
		*out = n;
	return true;
}

struct segment_table_entry
{
	uint32_t start_addr;
	uint32_t size;
};

// TODO maximum of 10 table entries are supported
struct segment_table_entry segment_table[256];
uint32_t segment_table_size;

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	if (scan32(&segment_table_size) == false)
	{
		fprintf(stderr, "Corrupted file\n");
		exit(-1);
	}
	fprintf(stderr, "segment table size %d\n", segment_table_size);

	if (segment_table_size == 0)
		return 0;

	for (size_t i = 0; i < segment_table_size; ++i)
	{
		uint32_t segmentStartAddr = 0;
		uint32_t segmentSize = 0;

		if (scan32(&segment_table[i].start_addr) == false)
		{
			fprintf(stderr, "Corrupted file\n");
			exit(-1);
		}
		if (scan32(&segment_table[i].size) == false)
		{
			fprintf(stderr, "Corrupted file\n");
			exit(-1);
		}

		fprintf(stderr, "segment start address %d\n", segment_table[i].start_addr);
		fprintf(stderr, "segment size %d\n", segment_table[i].size);
	}

	for (size_t i = 0; i < segment_table_size; ++i)
	{
		uint32_t current_addr = segment_table[i].start_addr;
		for (size_t j = 0; j < segment_table[i].size; ++j)
		{
			page_t *page = mem_access(current_addr);
			if (page == NULL)
			{
				page = mem_create(current_addr);
				if (page == NULL)
				{
					fprintf(stderr, "Allocation error\n");
					exit(-1);
				}
			}

			int c;
			c = fgetc(stdin);
			if (c == EOF)
			{
				fprintf(stderr, "Corrupted file\n");
				exit(-1);
			}
			mem_write_ex(page, current_addr++, c);
			fprintf(stderr, "%02x: %02x\n", current_addr-1, c);
		}
	}

	build_lookup_tables();

	while (fetch_next_inst())
	{
		if (skip_counter)
		{
			if (skip_counter-- == 1)
				continue;
		}

		if (magic_to_type_table[fetched_inst_params.magic] == ITYP_UNKNOWN)
		{
			fprintf(stderr, "Unknown instruction\n");
			exit(-1);
		}

		// jump to do_ functions
		int (*do_func)() = do_funcs[fetched_inst_params.magic];
		if (do_func)
		{
			if (do_func())
			{
				fprintf(stderr, "Error while executing instruction 0x%02x\n", fetched_inst_params.magic);
				exit(-1);
			}

			printf("successfully executed 0x%02x\n", fetched_inst_params.magic);
		}
		else
		{
			fprintf(stderr, "Instruction implementation is not found for 0x%02x\n", fetched_inst_params.magic);
			exit(-1);
		}
	}

	return 0;
}