global start
extern kernel_main

MULTIBOOT_PAGE_ALIGN    equ     1<<0
MULTIBOOT_MEMORY_INFO   equ     1<<1
MULTIBOOT_VIDEO_MODE    equ     1<<2
MULTIBOOT_INFO_FRAMEBUFFER_INFO  equ       0x00001000
MULTIBOOT_INFO_MEM_MAP  equ     0x00000040
MULTIBOOT_FLAGS         equ     MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_INFO_MEM_MAP | MULTIBOOT_VIDEO_MODE | MULTIBOOT_INFO_FRAMEBUFFER_INFO
MULTIBOOT_MAGIC         equ     0x1BADB002
MULTIBOOT_CHECKSUM      equ     -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

section .multiboot
align 4
    dd MULTIBOOT_MAGIC                                ; magic number (multiboot 2)
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

section .text
bits 32
start:
        ; The bootloader has loaded us into 32-bit protected mode on a i386
        ; machine. Interrupts are disabled. Paging is disabled. The processor
        ; state is as defined in the multiboot standard. The kernel has full
        ; control of the CPU.

        ; set up stack
        mov esp, stack_top

        call kernel_main

        hlt

section .bss
align 16
    stack_bottom: resb 0x100000                    ; 1M
    stack_top: