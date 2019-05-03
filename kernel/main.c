#include <stdio.h>
#include <kernel/vga.h>
#include <string.h>
#include <kernel/i386/segment.h>
#include <kernel/i386/multiboot.h>
#include <kernel/i386/util.h>
#include <kernel/i386/register.h>
#include <kernel/i386/page.h>

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

    page_init();
//    printf("%d \n", page_is_mapped(page_index(0, 0)));
//    printf("%d \n", page_is_mapped(page_index(0, 1)));
//    printf("%d \n", page_is_mapped(page_index(768, 0)));
//    printf("%d \n", page_is_mapped(page_index(768, 1)));
//    printf("%d \n", page_is_mapped(page_index(769, 0)));
//    printf("%d \n", page_is_mapped(page_index(772, 0)));
    printf("%#x \n", *page_directory_ptr);
    printf("%#x \n", *page_tables_ptr);
    printf("%#p \n", page_directory_ptr);
    printf("%#p \n", page_tables_ptr);
    printf("%#p \n", page_tables_ptr[0]);
//

    printf("%#p 000\n", (*page_directory_ptr)[0]);
    printf("%#p 111\n", (*page_tables_ptr)[0]);
//    printf("%#x \n", page_tables[768]);
//    printf("%#x \n", page_tables[769]);
//    printf("%#x \n", page_tables[770]);
}