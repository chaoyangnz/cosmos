#include <kernel/vmm.h>
#include <kernel/register.h>

uint8_t page_bitmap[ALL_PAGES / 8];

uint32_t
vmm__page_index(uint32_t page_table_index, uint32_t page_index_in_table) {
    return page_table_index * 1024 + page_index_in_table;
}

void
vmm__setup() {
    for(int i = 0; i < KERNEL_HIGH_HALF_SIZE; ++i) {
        uint32_t page_from = vmm__page_index(768 + i, 0);
        uint32_t page_to = vmm__page_index(768 + i, 1023);
        for(uint32_t page = page_from; page <= page_to; ++page) {
            vmm__set_page_mapped(page);
        }
    }
}

void
vmm__set_page_mapped(uint32_t page_index) {
    uint32_t index = page_index / 8;
    uint8_t offset = page_index % 8;
    page_bitmap[index] |= 0x1 << offset;
}

bool_t
vmm__is_page_mapped(uint32_t page_index) {
    uint32_t index = page_index / 8;
    uint8_t offset = page_index % 8;
    return (page_bitmap[index] & 0x1 << offset) > 0 ? true : false;
}