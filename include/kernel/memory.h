#ifndef COSMOS_MEMORY_H
#define COSMOS_MEMORY_H

#define KERNEL_BASE 0xC0000000
#define PHYSICAL_BASE 0x0

// 768; from this page table, kernel will be mapped to high half
#define KERNEL_PAGE_TABLE_INDEX (KERNEL_BASE >> 22)

// 4K
#define SIZE_PER_PAGE (4 * 1024)
// 4M
#define SIZE_PER_PAGE_TABLE (SIZE_PER_PAGE * 1024)
// 4G
#define SIZE_PER_PAGE_DIRECTORY (SIZE_PER_PAGE_TABLE * 1024)
// in total how many 4M are mapped to high half (unit 4M), here 4 means 4 * 4M = 16M
#define KERNEL_HIGH_HALF_SIZE 4

// 1024 * 1024 = 1M pages
#define ALL_PAGES (SIZE_PER_PAGE_DIRECTORY / SIZE_PER_PAGE)

#define va_to_pa(va) ((addr_t)(va) - KERNEL_BASE)
#define pa_to_va(pa) ((addr_t)(pa) + KERNEL_BASE)

#endif //COSMOS_MEMORY_H
