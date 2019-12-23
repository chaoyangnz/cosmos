#ifndef COSMOS_BOOT_H
#define COSMOS_BOOT_H

#include <compiler.h>
#include <stdint.h>

#define STACK_SIZE 4 * 1024

typedef uint8_t stack_t[STACK_SIZE];

extern stack_t stack;
extern uint8_t *stack_bottom;
extern uint8_t *stack_top;

extern void boot() BOOT_SECTION;
extern void after_boot() BOOT_SECTION;

extern void boot__setup_multiboot() BOOT_SECTION;
extern void boot__setup_page() BOOT_SECTION;
extern void boot__setup_segment() BOOT_SECTION;

extern void boot__fix_page_after_boot();
extern void boot__fix_segment_after_boot();

#endif //COSMOS_BOOT_H
