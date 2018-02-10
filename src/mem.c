#include "redcomp/comp/mem.h"

#define LVL1_OFF(addr) ((addr >> 48) & 0xFFFF)
#define LVL2_OFF(addr) ((addr >> 32) & 0xFFFF)
#define LVL3_OFF(addr) ((addr >> 16) & 0xFFFF)
#define LVL4_OFF(addr) (addr & 0xFFFF)

seg_tab_t seg_tab_lvl1;

void seg_tab_init(seg_tab_t *tab)
{
	for (size_t i = 0; i < 65536; ++i)
		tab->entry[i].tab = NULL;
}

void seg_init(seg_t *seg)
{
	for (size_t i = 0; i < 65536; ++i)
		seg->buf[i] = 0;
}

void mem_init()
{
	seg_tab_init(&seg_tab_lvl1);
}

seg_t* mem_check(uint64_t addr)
{
	seg_tab_t *seg_tab_lvl2 = seg_tab_lvl1.entry[LVL1_OFF(addr)].tab;
	if (seg_tab_lvl2 == NULL)
		return NULL;

	seg_tab_t *seg_tab_lvl3 = seg_tab_lvl2->entry[LVL2_OFF(addr)].tab;
	if (seg_tab_lvl3 == NULL)
		return NULL;

	seg_t *seg = seg_tab_lvl3->entry[LVL3_OFF(addr)].seg;
	return seg;
}

seg_t* mem_create(uint64_t addr)
{
	seg_t *seg = mem_check(addr);
	if (seg)
	{
		seg_init(seg);
		return seg;
	}

	seg_tab_t *seg_tab_lvl2 = seg_tab_lvl1.entry[LVL1_OFF(addr)].tab;
	if (seg_tab_lvl2 == NULL)
	{
		seg_tab_lvl2 = malloc(sizeof(seg_tab_t));
		if (seg_tab_lvl2 == NULL)
			return NULL;
		seg_tab_init(seg_tab_lvl2);
		seg_tab_lvl1.entry[LVL1_OFF(addr)].tab = seg_tab_lvl2;
	}

	seg_tab_t *seg_tab_lvl3 = seg_tab_lvl2->entry[LVL2_OFF(addr)].tab;
	if (seg_tab_lvl3 == NULL)
	{
		seg_tab_lvl3 = malloc(sizeof(seg_tab_t));
		if (seg_tab_lvl3 == NULL)
			return NULL;
		seg_tab_init(seg_tab_lvl3);
		seg_tab_lvl2->entry[LVL2_OFF(addr)].tab = seg_tab_lvl3;
	}

	seg = seg_tab_lvl3->entry[LVL3_OFF(addr)].seg;
	if (seg == NULL)
	{
		seg = malloc(sizeof(seg_t));
		if (seg == NULL)
			return NULL;
		seg_init(seg);
		seg_tab_lvl3->entry[LVL3_OFF(addr)].seg = seg;
	}

	return seg;
}

void mem_destroy(uint64_t addr)
{
	seg_t *seg = mem_check(addr);
	if (seg == NULL)
		return;

	seg_tab_t *seg_tab_lvl3 = seg_tab_lvl1.entry[LVL1_OFF(addr)].tab->entry[LVL2_OFF(addr)].tab;
	free(seg_tab_lvl3->entry[LVL3_OFF(addr)].seg);
	seg_tab_lvl3->entry[LVL3_OFF(addr)].seg = NULL;
}

int mem_read(uint64_t addr)
{
	seg_t* seg = mem_check(addr);
	if (seg)
		return seg->buf[LVL4_OFF(addr)];
	else
		return -1;
}

int mem_read_ex(seg_t *seg, uint64_t addr)
{
	if (seg)
		return seg->buf[LVL4_OFF(addr)];
	else
		return -1;
}

int mem_write(uint64_t addr, uint8_t val)
{
	seg_t* seg = mem_check(addr);
	if (seg)
	{
		seg->buf[LVL4_OFF(addr)] = val;
		return val;
	}
	else
		return -1;
}

bool mem_dump(uint64_t addr)
{
	seg_t *seg = mem_check(addr);
	if (seg == NULL)
		return false;
	fprintf(stderr, "Dumping page %016llx\n", addr);
	for (size_t i = 0; i < 65536; ++i)
		fprintf(stderr, "%02x ", seg->buf[i]);
	fprintf(stderr, "\n");
	return true;
}

bool mem_read_inst(uint64_t addr, uint16_t *out)
{
	uint16_t tmp = 0;

	// check if addr spans more than one segment
	uint64_t seg1 = addr / 65536;
	uint64_t seg2 = (addr+1) / 65536;
	if (seg1 == seg2)
	{
		seg_t *seg = mem_check(addr);
		if (seg == NULL)
			return false;
		tmp = mem_read_ex(seg, addr) << 8;
		tmp |= mem_read_ex(seg, addr+1);
	}
	else
	{
		seg_t *seg1 = mem_check(addr);
		if (seg1 == NULL)
			return false;
		seg_t *seg2 = mem_check(addr+1);
		if (seg2 == NULL)
			return false;
		tmp = mem_read_ex(seg1, addr) << 8;
		tmp |= mem_read_ex(seg2, addr+1);
	}
	if (out)
		*out = tmp;
	return true;
}