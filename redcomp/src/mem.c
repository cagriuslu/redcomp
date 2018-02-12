#include "redcomp/comp/mem.h"
#include "redcomp/comp/globals.h"

#define LVL1_OFF(addr) ((addr >> 48) & 0xFFFF)
#define LVL2_OFF(addr) ((addr >> 32) & 0xFFFF)
#define LVL3_OFF(addr) ((addr >> 16) & 0xFFFF)
#define LVL4_OFF(addr) (addr & 0xFFFF)

page_t* mem_access(uint64_t address)
{
	page_table_t *pt_lvl2 = pt_lvl1.entry[LVL1_OFF(address)].child_table;
	if (!pt_lvl2)
		return NULL;

	page_table_t *pt_lvl3 = pt_lvl2->entry[LVL2_OFF(address)].child_table;
	if (!pt_lvl3)
		return NULL;

	page_t *p = pt_lvl3->entry[LVL3_OFF(address)].page;
	return p;
}

page_t* mem_create(uint64_t address)
{
	page_t *p = mem_access(address);
	if (p)
	{
		memset(p->buffer, 0, 65536);
		return p;
	}

	page_table_t *pt_lvl2 = pt_lvl1.entry[LVL1_OFF(address)].child_table;
	if (!pt_lvl2)
	{
		pt_lvl2 = calloc(1, sizeof(page_table_t));
		if (!pt_lvl2)
			return NULL;
		pt_lvl1.entry[LVL1_OFF(address)].child_table = pt_lvl2;
	}

	page_table_t *pt_lvl3 = pt_lvl2->entry[LVL2_OFF(address)].child_table;
	if (!pt_lvl3)
	{
		pt_lvl3 = calloc(1, sizeof(page_table_t));
		if (!pt_lvl3)
			return NULL;
		pt_lvl2->entry[LVL2_OFF(address)].child_table = pt_lvl3;
	}

	p = pt_lvl3->entry[LVL3_OFF(address)].page;
	if (!p)
	{
		p = calloc(1, sizeof(page_t));
		if (!p)
			return NULL;
		pt_lvl3->entry[LVL3_OFF(address)].page = p;
	}

	return p;
}

void mem_destroy(uint64_t address)
{
	page_t *p = mem_access(address);
	if (p)
	{
		page_table_t *pt_lvl2 = pt_lvl1.entry[LVL1_OFF(address)].child_table;
		page_table_t *pt_lvl3 = pt_lvl2->entry[LVL2_OFF(address)].child_table;
		free(pt_lvl3->entry[LVL3_OFF(address)].page);
		pt_lvl3->entry[LVL3_OFF(address)].page = NULL;
	}
}

int mem_read(uint64_t address)
{
	page_t *p = mem_access(address);
	return mem_read_ex(p, address);
}

int mem_read_ex(page_t *page, uint64_t address)
{
	if (page)
		return page->buffer[LVL4_OFF(address)];
	else
		return -1;
}

int mem_write(uint64_t address, uint8_t value)
{
	page_t *p = mem_access(address);
	return mem_write_ex(p, address, value);
}

int mem_write_ex(page_t *page, uint64_t address, uint8_t value)
{
	if (page)
	{
		page->buffer[LVL4_OFF(address)] = value;
		return value;
	}
	else
		return -1;
}

int mem_dump(uint64_t address)
{
	page_t *p = mem_access(address);
	if (!p)
		return -1;

	fprintf(stderr, "Dumping page starting from address %016llx\n", address);
	for (size_t i = LVL4_OFF(address); i < 65536; ++i)
		fprintf(stderr, "%02x ", p->buffer[i]);
	fprintf(stderr, "\n");
	return 0;
}

bool mem_read_16_big(uint64_t address, uint16_t *out)
{
	uint16_t tmp = 0;
	size_t byte_count = 2;
	for (size_t i = 0; i < byte_count; ++i)
	{
		int byte = mem_read(address + i);
		if (byte == -1)
			return false;
		tmp |= byte << (8 * (byte_count - 1 - i));
	}
	if (out)
		*out = tmp;
	return true;
}
bool mem_read_32_big(uint64_t address, uint32_t *out)
{
	uint32_t tmp = 0;
	size_t byte_count = 4;
	for (size_t i = 0; i < byte_count; ++i)
	{
		int byte = mem_read(address + i);
		if (byte == -1)
			return false;
		tmp |= byte << (8 * (byte_count - 1 - i));
	}
	if (out)
		*out = tmp;
	return true;
}
bool mem_read_64_big(uint64_t address, uint64_t *out)
{
	uint64_t tmp = 0;
	size_t byte_count = 8;
	for (size_t i = 0; i < byte_count; ++i)
	{
		int byte = mem_read(address + i);
		if (byte == -1)
			return false;
		tmp |= byte << (8 * (byte_count - 1 - i));
	}
	if (out)
		*out = tmp;
	return true;
}
bool mem_read_16_little(uint64_t address, uint16_t *out)
{
	uint16_t tmp = 0;
	size_t byte_count = 2;
	for (size_t i = 0; i < byte_count; ++i)
	{
		int byte = mem_read(address + i);
		if (byte == -1)
			return false;
		tmp |= byte << (8 * i);
	}
	if (out)
		*out = tmp;
	return true;
}
bool mem_read_32_little(uint64_t address, uint32_t *out)
{
	uint32_t tmp = 0;
	size_t byte_count = 4;
	for (size_t i = 0; i < byte_count; ++i)
	{
		int byte = mem_read(address + i);
		if (byte == -1)
			return false;
		tmp |= byte << (8 * i);
	}
	if (out)
		*out = tmp;
	return true;
}
bool mem_read_64_little(uint64_t address, uint64_t *out)
{
	uint64_t tmp = 0;
	size_t byte_count = 8;
	for (size_t i = 0; i < byte_count; ++i)
	{
		int byte = mem_read(address + i);
		if (byte == -1)
			return false;
		tmp |= byte << (8 * i);
	}
	if (out)
		*out = tmp;
	return true;
}
