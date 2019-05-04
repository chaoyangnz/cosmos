#ifndef COSMOS_VMM_H
#define COSMOS_VMM_H

#include <stdint.h>
#include <kernel/page.h>

//extern uint8_t page_bitmap[ALL_PAGES / 8];

extern void vmm__setup();
extern uint32_t vmm__page_index(uint32_t page_table_index, uint32_t page_index_in_table);
extern void vmm__set_page_mapped(uint32_t page_index);
extern bool_t vmm__is_page_mapped(uint32_t page_index);

#endif //COSMOS_VMM_H
