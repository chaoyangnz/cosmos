#ifndef COSMOS_PAGE_H
#define COSMOS_PAGE_H

#include <stdint.h>
#include <stdbool.h>

#define KERNEL_MAPPED_4M 4

#define PAGE_MAP_SIZE 4 * 1024
#define PAGE_NUMBER 1024 * 1024

#include <kernel/i386/eden.h>

extern uint32_t (*page_directory_ptr)[1024];
extern page_table_t (*page_tables_ptr)[1024];

extern uint8_t page_bitmap[PAGE_NUMBER / 8];

extern void page_init();
extern uint32_t page_index(uint32_t page_table_index, uint32_t page_index_in_table);
extern void page_mapped(uint32_t index);
extern bool_t page_is_mapped(uint32_t index);


#endif //COSMOS_PAGE_H
