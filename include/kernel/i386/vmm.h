#ifndef COSMOS_VMM_H
#define COSMOS_VMM_H

#include <stdint.h>
#include <kernel/i386/page.h>

//extern uint8_t page_bitmap[ALL_PAGES / 8];

extern void mm_init();
extern uint32_t mm_page_index(uint32_t page_table_index, uint32_t page_index_in_table);
extern void mm_set_page_mapped(uint32_t page_index);
extern bool_t mm_is_page_mapped(uint32_t page_index);

#endif //COSMOS_VMM_H
