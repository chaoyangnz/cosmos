#ifndef COSMOS_PAGE_H
#define COSMOS_PAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "layout.h"

typedef uint32_t page_table_t[1024]; // (1024 pages) * 4k = 4M
typedef uint32_t page_directory_t[1024];
typedef page_table_t page_tables_t[1024];

// defined in ASM and these structures can be accessed after paging is enabled. If you need to access before paging
// is enabled, use page_directory_ptr and page_tables_ptr instead
extern page_directory_t page_directory __attribute__((aligned(0x1000)));
extern page_tables_t page_tables __attribute__((aligned(0x1000)));



#endif //COSMOS_PAGE_H
