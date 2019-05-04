#include <stdio.h>
#include <kernel/vga.h>
#include <string.h>
#include <kernel/segment.h>
#include <kernel/multiboot.h>
#include <kernel/util.h>
#include <kernel/register.h>
#include <kernel/vmm.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This kernel will only work for the 32-bit i386 targets. */
#if !defined(__i386__)
#error "This kernel needs to be compiled with a i386-elf compiler"
#endif

void kernel_main()
{
    /* Initialize terminal interface */
    vga_initialize();
    /* Welcome screen */
    printf("%s", "   ___   ___    __  ___  ___   ___    __ \n  //    // \\\\  (( \\ ||\\\\//||  // \\\\  (( \\\n ((    ((   ))  \\\\  || \\/ || ((   ))  \\\\ \n  \\\\__  \\\\_//  \\_)) ||    ||  \\\\_//  \\_))\n\n");
    printf("%s", "               Hello, Cosmos!\n");
    vga_set_fg(VGA_COLOR_BROWN);

    multiboot_print();

    /* re-setup GDT after paging is enabled */
    gdt_init();
    gdt_load();
    gdt_print();

    mm_init();
    printf("%d \n", mm_is_page_mapped(mm_page_index(0, 0)));
    printf("%d \n", mm_is_page_mapped(mm_page_index(0, 1)));
    printf("%d \n", mm_is_page_mapped(mm_page_index(768, 0)));
    printf("%d \n", mm_is_page_mapped(mm_page_index(768, 1)));
    printf("%d \n", mm_is_page_mapped(mm_page_index(769, 0)));
    printf("%d \n", mm_is_page_mapped(mm_page_index(772, 0)));
    printf("%#x \n", &page_directory);
    printf("%#x \n", &page_tables);
}