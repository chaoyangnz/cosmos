#ifndef COSMOS_PAGE_H
#define COSMOS_PAGE_H

#include <stdint.h>
#include <stdbool.h>


#define VIRTUAL_START 0xC0000000
#define PHYSICAL_START 0x0
// in total how many 4M
#define KERNEL_HIGH_HALF_SIZE_IN_4M 4
// 4K
#define PAGE_MAP_SIZE (4 * 1024)
#define PAGE_TABLE_MAP_SIZE (PAGE_MAP_SIZE * 1024)

#define KERNEL_MAPPED_4M 4

#define PAGES_TOTAL 1024 * 1024

// 768
#define KERNEL_PAGE_TABLE_INDEX_START (VIRTUAL_START >> 22)

#define va_to_pa(va) ((addr_t)(va) - VIRTUAL_START)
#define pa_to_va(pa) ((addr_t)(pa) + VIRTUAL_START)


typedef uint32_t page_table_t[1024]; // (1024 pages) * 4k = 4M

// defined in ASM
extern uint32_t page_directory[1024];
extern page_table_t page_tables[1024];

// Only used in boot
extern void boot_init_page_directory() __attribute__((section (".boot")));
extern void boot_map_page_table(uint32_t page_table_index) __attribute__((section (".boot")));
extern void boot_map_high_half_pages() __attribute__((section (".boot")));


extern uint32_t (*page_directory_ptr)[1024];
extern page_table_t (*page_tables_ptr)[1024];

extern uint8_t page_bitmap[PAGES_TOTAL / 8];

extern void page_map_init();
extern uint32_t page_index(uint32_t page_table_index, uint32_t page_index_in_table);
extern void page_mapped(uint32_t index);
extern bool_t page_is_mapped(uint32_t index);


#endif //COSMOS_PAGE_H
