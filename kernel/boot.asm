global start

extern stack_top
extern boot
extern after_boot
extern kernel_main

KERNEL_BASE     equ     0xC0000000

MULTIBOOT_PAGE_ALIGN    equ     1<<0
MULTIBOOT_MEMORY_INFO   equ     1<<1
MULTIBOOT_VIDEO_MODE    equ     1<<2
MULTIBOOT_INFO_FRAMEBUFFER_INFO  equ       0x00001000
MULTIBOOT_INFO_MEM_MAP  equ     0x00000040
MULTIBOOT_FLAGS         equ     MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_INFO_MEM_MAP | MULTIBOOT_VIDEO_MODE | MULTIBOOT_INFO_FRAMEBUFFER_INFO
MULTIBOOT_MAGIC         equ     0x1BADB002
MULTIBOOT_CHECKSUM      equ     -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

section .boot
bits 32
align 0x1000
multiboot:
    dd MULTIBOOT_MAGIC                                ; magic number (multiboot 2)
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM
start:
    cli
    ;;; stack in identity mapping
    mov esp, stack_top - KERNEL_BASE
    ;;; enable segment, paging
    call boot

    ;;;-------------------------------------------
    ;;;     kernel is running in high half
    ;;;------------------------------------------
    ;;; re-setup stack
    mov esp, stack_top
    ;;; fix virtual address & recycle identity page table
    call after_boot

    ;;;------------HAPPY WORLD--------------------
    call kernel_main

    hlt

