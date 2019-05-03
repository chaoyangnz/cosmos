#include <kernel/i386/page.h>

uint32_t (*page_directory_ptr)[1024] = (uint32_t *)((void *)page_directory + VIRTUAL_START);
page_table_t (*page_tables_ptr)[1024] = (page_table_t *)((void *)page_tables + VIRTUAL_START);

uint8_t page_bitmap[PAGE_NUMBER / 8];

uint32_t page_index(uint32_t page_table_index, uint32_t page_index_in_table) {
    return page_table_index * 1024 + page_index_in_table;
}

void recycle_identity_mapping() {
    for(uint32_t page_table_index = 0; page_table_index < KERNEL_HIGH_HALF_SIZE_IN_4M; ++page_table_index) {
        for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
            (*page_tables_ptr)[page_table_index][page_index] &= ~0x00000001;
        }
    }
}

void
page_init() {
    recycle_identity_mapping();
    for(int i = 0; i < KERNEL_MAPPED_4M; ++i) {
        uint32_t page_from = page_index(768 + i, 0);
        uint32_t page_to = page_index(768 + i, 1023);
        for(uint32_t page = page_from; page <= page_to; ++page) {
            page_mapped(page);
        }
    }
}

void
page_mapped(uint32_t pos) {
    uint32_t index = pos / 8;
    uint8_t offset = pos % 8;
    page_bitmap[index] |= 0x1 << offset;
}

bool_t
page_is_mapped(uint32_t pos) {
    uint32_t index = pos / 8;
    uint8_t offset = pos % 8;
    return (page_bitmap[index] & 0x1 << offset) > 0 ? true : false;
}