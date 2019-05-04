#include <kernel/i386/vmm.h>

uint8_t page_bitmap[ALL_PAGES / 8];

static void mm_recycle_identity_mapping() {
    for(uint32_t page_table_index = 0; page_table_index < KERNEL_HIGH_HALF_SIZE; ++page_table_index) {
        for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
            page_tables[page_table_index][page_index] &= ~0x00000001;
        }
    }
}

uint32_t
mm_page_index(uint32_t page_table_index, uint32_t page_index_in_table) {
    return page_table_index * 1024 + page_index_in_table;
}

void
mm_init() {
    mm_recycle_identity_mapping();
    for(int i = 0; i < KERNEL_HIGH_HALF_SIZE; ++i) {
        uint32_t page_from = mm_page_index(768 + i, 0);
        uint32_t page_to = mm_page_index(768 + i, 1023);
        for(uint32_t page = page_from; page <= page_to; ++page) {
            mm_set_page_mapped(page);
        }
    }
}

void
mm_set_page_mapped(uint32_t page_index) {
    uint32_t index = page_index / 8;
    uint8_t offset = page_index % 8;
    page_bitmap[index] |= 0x1 << offset;
}

bool_t
mm_is_page_mapped(uint32_t page_index) {
    uint32_t index = page_index / 8;
    uint8_t offset = page_index % 8;
    return (page_bitmap[index] & 0x1 << offset) > 0 ? true : false;
}