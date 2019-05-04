#ifndef COSMOS_PAGE_H
#define COSMOS_PAGE_H

#include <stdint.h>
#include <stdbool.h>
#include <kernel/memory.h>

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

extern void page__setup() __attribute__((section (".boot")));
extern void page__map_page_table(uint32_t page_table_index) __attribute__((section (".boot")));
extern void page__map_high_half_pages() __attribute__((section (".boot")));
extern void page__enable_paging() __attribute__((section (".boot")));

#endif //COSMOS_PAGE_H
