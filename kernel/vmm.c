#include <kernel/vmm.h>
#include <kernel/register.h>

uint8_t page_bitmap[ALL_PAGES / 8];

static void vmm__recycle_identity_mapping() {
    for(uint32_t page_table_index = 0; page_table_index < KERNEL_HIGH_HALF_SIZE; ++page_table_index) {
        for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
            page_tables[page_table_index][page_index] &= ~0x00000001;
        }
    }
}

//static void vmm__fix_gdt_va() {
//    set_gdtr()
//}

uint32_t
vmm__page_index(uint32_t page_table_index, uint32_t page_index_in_table) {
    return page_table_index * 1024 + page_index_in_table;
}

void
vmm__setup() {
    vmm__recycle_identity_mapping();
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