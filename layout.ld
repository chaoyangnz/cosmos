ENTRY(start)

SECTIONS {
    virtual_start = 0xC0000000;
    physical_start = 0x0;
    kernel_offset = 0x100000;
    kernel_virtual_start = virtual_start + kernel_offset;
    kernel_physical_start = kernel_offset;

    . = kernel_offset;

    .boot 0x100000 : AT(0x100000) ALIGN(4K)
    {
        *(.multiboot)
        *(.boot)
        *(.boot_data)
    }


    . += virtual_start;
    .text ALIGN(4K) : AT(ADDR(.text) - virtual_start)
    {
        *(.text)
    }

    /* Read-only data. */
    .rodata ALIGN(4K) : AT(ADDR(.rodata) - virtual_start)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data ALIGN(4K) : AT(ADDR(.data) - virtual_start)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss ALIGN(4K) : AT(ADDR(.bss) - virtual_start)
    {
        *(COMMON)
        *(.bss)
    }
}