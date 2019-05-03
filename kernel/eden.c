#include <kernel/i386/eden.h>

void boot_init_page_directory() {
    for(uint32_t page_table_index = 0; page_table_index < 1024; ++page_table_index) {
        for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
            page_tables[page_table_index][page_index] = 0x00000002; // pages not present bit
        }
        page_directory[page_table_index] = (addr_t)((page_table_t *)&page_tables[page_table_index]) | 0x00000003; // page table present
    }
}

void boot_map_page_table(uint32_t page_table_index) {
    uint32_t page_table_physical_start = PHYSICAL_START + (page_table_index % KERNEL_PAGE_TABLE_INDEX_START) * PAGE_TABLE_MAP_SIZE;
    for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
        page_tables[page_table_index][page_index] = (page_table_physical_start + page_index * PAGE_MAP_SIZE) | 0x00000003;
    }
}

void boot_map_high_half_pages() {
    for(uint32_t page_table_index = 0; page_table_index < KERNEL_HIGH_HALF_SIZE_IN_4M; ++page_table_index) {
        boot_map_page_table(page_table_index);
        boot_map_page_table(page_table_index + KERNEL_PAGE_TABLE_INDEX_START);
    }
}

