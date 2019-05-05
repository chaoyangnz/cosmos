#ifndef COSMOS_VMM_H
#define COSMOS_VMM_H

#include <stdint.h>
#include <stdbool.h>
#include <kernel/memory.h>
#include <kernel/page.h>

extern void vmm__setup();
extern uint32_t vmm__page_index(uint32_t page_table_index, uint32_t page_index_in_table);
extern void vmm__set_page_mapped(uint32_t page_index);
extern bool_t vmm__is_page_mapped(uint32_t page_index);

extern void vmm__info();

#endif //COSMOS_VMM_H
