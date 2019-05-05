#include <kernel/multiboot.h>
#include <stdio.h>
#include <kernel/memory.h>

multiboot_info_t multiboot_info;

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