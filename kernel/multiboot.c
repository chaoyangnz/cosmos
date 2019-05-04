#include <kernel/multiboot.h>
#include <stdio.h>
#include <kernel/memory.h>

multiboot_info_t *multiboot_info_ptr;

void
multiboot__setup() {
    multiboot_info_t *mbi;
	asm("movl %%ebx, %0"
	: "=r" (mbi));
    multiboot_info_ptr = (multiboot_info_t *)pa_to_va(mbi);
}

void
multiboot__info() {
    /* Multiboot Info */
    printf("Memory: 0 - %s ****  1M - %s \n", humanize_size(multiboot_info_ptr->mem_lower * 1024),
           humanize_size((uint64_t) multiboot_info_ptr->mem_upper * 1024));
    printf("Video: 0x%x %d x %d %d\n", pa_to_va(multiboot_info_ptr->framebuffer_addr), multiboot_info_ptr->framebuffer_width, multiboot_info_ptr->framebuffer_height, multiboot_info_ptr->framebuffer_type);

    printf("Memory map: %#x (%d) \n", pa_to_va(multiboot_info_ptr->mmap_addr), multiboot_info_ptr->mmap_length);
    multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)pa_to_va(multiboot_info_ptr->mmap_addr);
    for(size_t i = 0; i < multiboot_info_ptr->mmap_length / 24; i++) {
        printf("%s from %#llx type: %u \n", humanize_size(mmap->len), mmap->addr, mmap->type);
        mmap = (void*)mmap + mmap->size + 4;
    }
}