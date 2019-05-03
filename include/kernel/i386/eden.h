#ifndef COSMOS_EDEN_H
#define COSMOS_EDEN_H

#include <stdint.h>

typedef uint32_t page_table_t[1024]; // (1024 pages) * 4k = 4M

#define VIRTUAL_START 0xC0000000
#define PHYSICAL_START 0x0
// in total how many 4M
#define KERNEL_HIGH_HALF_SIZE_IN_4M 4
// 4K
#define PAGE_MAP_SIZE (4 * 1024)
#define PAGE_TABLE_MAP_SIZE (PAGE_MAP_SIZE * 1024)
// 768
#define KERNEL_PAGE_TABLE_INDEX_START (VIRTUAL_START >> 22)

extern uint32_t page_directory[1024];
extern page_table_t page_tables[1024];

extern void boot_init_page_directory() __attribute__((section (".boot")));
extern void boot_map_page_table(uint32_t page_table_index) __attribute__((section (".boot")));
extern void boot_map_high_half_pages() __attribute__((section (".boot")));

#endif //COSMOS_EDEN_H
