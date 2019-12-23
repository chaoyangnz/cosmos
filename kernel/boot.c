#include "boot.h"

void boot() {
    boot__setup_multiboot();
    boot__setup_segment();
    boot__setup_page();
}

void after_boot() {
    boot__fix_segment_after_boot();
    boot__fix_page_after_boot();
}