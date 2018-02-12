#pragma once
#include "defs.h"

void mem_init();
void mem_page_table_init(page_table_t *pt);
void mem_page_init(page_t *p);
page_t* mem_access(uint64_t address);
page_t* mem_create(uint64_t address);
void mem_destroy(uint64_t address);
int mem_read(uint64_t address);
int mem_read_ex(page_t *page, uint64_t address);
int mem_read_multi(uint64_t address, uint8_t *destination, size_t count); // not yet implemented
int mem_write(uint64_t address, uint8_t value);
int mem_write_ex(page_t *page, uint64_t address, uint8_t value);
int mem_write_multi(uint64_t address, uint8_t *source, size_t count); // not yet implemented

bool mem_read_16_big(uint64_t address, uint16_t *out);
bool mem_read_32_big(uint64_t address, uint32_t *out);
bool mem_read_64_big(uint64_t address, uint64_t *out);
bool mem_read_16_little(uint64_t address, uint16_t *out);
bool mem_read_32_little(uint64_t address, uint32_t *out);
bool mem_read_64_little(uint64_t address, uint64_t *out);

// Debug
int mem_dump(uint64_t address);
