#include <kernel/multiboot.h>
#include <stdio.h>
#include <kernel/page.h>

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
    printf("Memory: 0 - %dK **** 1M - %dM \n", multiboot_info_ptr->mem_lower + 1, 1 + (multiboot_info_ptr->mem_upper/1024) + 1);
    printf("Video: 0x%x %d x %d %d\n", pa_to_va(multiboot_info_ptr->framebuffer_addr), multiboot_info_ptr->framebuffer_width, multiboot_info_ptr->framebuffer_height, multiboot_info_ptr->framebuffer_type);

    printf("Memory map: %#x (%d) \n", pa_to_va(multiboot_info_ptr->mmap_addr), multiboot_info_ptr->mmap_length);
    multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)pa_to_va(multiboot_info_ptr->mmap_addr);
    for(size_t i = 0; i < multiboot_info_ptr->mmap_length / 24; i++) {
        printf("size: %u addr: %#llx  len: %#llx type: %u \n", mmap->size,  mmap->addr, mmap->len, mmap->type);
        mmap = (void*)mmap + mmap->size + 4;
    }
}