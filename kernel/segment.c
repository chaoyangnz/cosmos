#include <kernel/segment.h>
#include <kernel/register.h>
#include <stdio.h>

gdt_t gdt;

void segment__info() {
    gdt_desc_t gdt_des = get_gdtr();
    printf("GDT: %#x %#x CS: %#x DS: %#x ES: %#x SS: %#x FS: %#x GS: %#x \n", \
        gdt_des.base, gdt_des.limit, get_cs(), get_ds(), get_es(), get_ss(), get_fs(), get_gs());
}



