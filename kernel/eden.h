#ifndef COSMOS_EDEN_H
#define COSMOS_EDEN_H

#include <compiler.h>

extern void boot() BOOT_SECTION;
extern void after_boot() BOOT_SECTION;

extern void multiboot__setup() BOOT_SECTION;
extern void page__setup() BOOT_SECTION;
extern void segment__setup() BOOT_SECTION;

extern void page__after_boot();
extern void segment__after_boot();

#endif //COSMOS_EDEN_H
