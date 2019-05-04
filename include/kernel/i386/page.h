#ifndef COSMOS_PAGE_H
#define COSMOS_PAGE_H

#include <stdint.h>
#include <stdbool.h>


#define KERNEL_BASE 0xC0000000
#define PHYSICAL_BASE 0x0
// in total how many 4M are mapped to high half (unit 4M), here 4 means 4 * 4M = 16M
#define KERNEL_HIGH_HALF_SIZE 4
// 768; from this page table, kernel will be mapped to high half
#define KERNEL_PAGE_TABLE_INDEX (KERNEL_BASE >> 22)

// 4K
#define SIZE_PER_PAGE (4 * 1024)
// 4M
#define SIZE_PER_PAGE_TABLE (SIZE_PER_PAGE * 1024)
// 4G
#define SIZE_PER_PAGE_DIRECTORY (SIZE_PER_PAGE_TABLE * 1024)
// 1024 * 1024 = 1M pages
#define ALL_PAGES SIZE_PER_PAGE_DIRECTORY / SIZE_PER_PAGE


#define va_to_pa(va) ((addr_t)(va) - KERNEL_BASE)
#define pa_to_va(pa) ((addr_t)(pa) + KERNEL_BASE)


typedef uint32_t page_table_t[1024]; // (1024 pages) * 4k = 4M
typedef uint32_t page_directory_t[1024];
typedef page_table_t page_tables_t[1024];

// defined in ASM and these structures can be accessed after paging is enabled. If you need to access before paging
// is enabled, use page_directory_ptr and page_tables_ptr instead
extern page_directory_t page_directory;
extern page_tables_t page_tables;


// --------------------------------------------------------------
//         Only used in boot when paging isn't enabled
// --------------------------------------------------------------

extern page_directory_t *page_directory_ptr __attribute__((section (".boot_bss")));
extern page_tables_t *page_tables_ptr __attribute__((section (".boot_bss")));

extern void boot_init_page_directory() __attribute__((section (".boot")));
extern void boot_map_page_table(uint32_t page_table_index) __attribute__((section (".boot")));
extern void boot_map_high_half_pages() __attribute__((section (".boot")));

#endif //COSMOS_PAGE_H
