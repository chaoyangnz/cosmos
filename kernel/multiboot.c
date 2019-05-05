#include <kernel/multiboot.h>
#include <stdio.h>
#include <kernel/memory.h>

multiboot_info_t multiboot_info;

void
multiboot__setup() {
    multiboot_info_t *multiboot_info_ptr_origin;
	asm("movl %%ebx, %0"
	: "=r" (multiboot_info_ptr_origin));
    multiboot_info_t *multiboot_info_ptr = (multiboot_info_t *)va_to_pa(&multiboot_info);
    // memcopy
    uint8_t *src = (uint8_t *)multiboot_info_ptr_origin;
    uint8_t *dst = (uint8_t *)multiboot_info_ptr;
    for(int i = 0; i < sizeof(multiboot_info_t); ++i) {
        *dst++ = *src++;
    }
    // copy and fix address
    multiboot_info_ptr->mmap_addr = pa_to_va(multiboot_info_ptr_origin->mmap_addr);
    multiboot_info_ptr->framebuffer_addr = pa_to_va(multiboot_info_ptr_origin->framebuffer_addr);
}

void
multiboot__info() {
    /* Multiboot Info */
    printf("Memory: 0 - %s ****  1M - %s \n", humanize_size(multiboot_info.mem_lower * 1024),
           humanize_size((uint64_t) multiboot_info.mem_upper * 1024));
    printf("Video: 0x%x %d x %d %d\n", multiboot_info.framebuffer_addr, multiboot_info.framebuffer_width, multiboot_info.framebuffer_height, multiboot_info.framebuffer_type);

    printf("Memory map: %#x (%d) \n", multiboot_info.mmap_addr, multiboot_info.mmap_length);
    multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)multiboot_info.mmap_addr;
    for(size_t i = 0; i < multiboot_info.mmap_length / 24; i++) {
        printf("%s from %#llx type: %u \n", humanize_size(mmap->len), mmap->addr, mmap->type);
        mmap = (void*)mmap + mmap->size + 4;
    }
}