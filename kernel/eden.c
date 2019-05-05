#include "eden.h"

void boot() {
    multiboot__setup();
    segment__setup();
    page__setup();
}

void after_boot() {
    segment__after_boot();
    page__after_boot();
}