#include <stdio.h>
#include <kernel/console.h>
#include <string.h>
#include <kernel/i386/segment.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This kernel will only work for the 32-bit i386 targets. */
#if !defined(__i386__)
#error "This kernel needs to be compiled with a i386-elf compiler"
#endif

void kernel_main(void)
{
    /* Initialize terminal interface */
    console_initialize();

    /* Newline support. */
    printf("%s", "   ___   ___    __  ___  ___   ___    __ \n  //    // \\\\  (( \\ ||\\\\//||  // \\\\  (( \\\n ((    ((   ))  \\\\  || \\/ || ((   ))  \\\\ \n  \\\\__  \\\\_//  \\_)) ||    ||  \\\\_//  \\_))\n\n");
    printf("%s", "               Hello, Cosmos!\n");
    gdt_init();
    gdt_load();
}