#include <kernel/multiboot.h>
#include <stdio.h>

void* fix_address(void *addr) {
    return addr + 0xC0000000;
}

multiboot_info_t*
multiboot_get() {
    multiboot_info_t* mbi;
	asm("movl %%ebx, %0"
	: "=r" (mbi));
	return fix_address(mbi);
}

void
multiboot_print() {
    /* Multiboot Info */
    multiboot_info_t* mbi = multiboot_get();
    printf("Memory: 0 - %dK **** 1M - %dM \n", mbi->mem_lower + 1, 1 + (mbi->mem_upper/1024) + 1);
    printf("Video: 0x%x %d x %d %d\n", fix_address(mbi->framebuffer_addr), mbi->framebuffer_width, mbi->framebuffer_height, mbi->framebuffer_type);

    printf("Memory map: %#x (%d) \n", fix_address(mbi->mmap_addr), mbi->mmap_length);
    multiboot_memory_map_t* mmap = fix_address(mbi->mmap_addr);
    for(size_t i = 0; i < mbi->mmap_length / 24; i++) {
        printf("size: %u addr: %#llx  len: %#llx type: %u \n", mmap->size,  mmap->addr, mmap->len, mmap->type);
        mmap = (void*)mmap + mmap->size + 4;
    }
}