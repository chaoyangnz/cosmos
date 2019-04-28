#include <stdio.h>
#include <kernel/vga.h>
#include <string.h>
#include <kernel/i386/segment.h>
#include <kernel/i386/multiboot.h>
#include <kernel/i386/util.h>
#include <kernel/i386/register.h>

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

    /* Segments setting */
    gdt_init();
    gdt_load();
    gdt_print();

}