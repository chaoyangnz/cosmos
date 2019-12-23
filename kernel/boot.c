#include "boot.h"

stack_t stack;
uint8_t *stack_bottom = &stack[0];
uint8_t *stack_top = &stack[STACK_SIZE-1];

void boot() {
    boot__setup_multiboot();
    boot__setup_segment();
    boot__setup_page();
}

void after_boot() {
    boot__fix_segment_after_boot();
    boot__fix_page_after_boot();
}