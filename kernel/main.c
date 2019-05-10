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

static void welcome() {
    printf("%s", "   ___   ___    __  ___  ___   ___    __ \n  //    // \\\\  (( \\ ||\\\\//||  // \\\\  (( \\\n ((    ((   ))  \\\\  || \\/ || ((   ))  \\\\ \n  \\\\__  \\\\_//  \\_)) ||    ||  \\\\_//  \\_))\n\n");
    printf("%s", "               Hello, Cosmos!\n");
    vga__set_fg(VGA_COLOR_BROWN);
}

void kernel_main()
{
    vga__setup();
    welcome();
    multiboot__info();

    vmm__setup();
    vmm__info();

    interrupt__setup();
}