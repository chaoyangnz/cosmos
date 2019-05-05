global start

extern stack_top
extern multiboot__setup
extern segment__setup
extern page__setup
extern kernel_main

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
        call multiboot__setup
        ;;;------------ENABLE SEGMENT--------------------
        ; setup GDT
        call segment__setup

        ;;;------------PAGING SETUP--------------------
        ; setup paging
        call page__setup

        ;;;------------HAPPY WORLD--------------------
        ; set up stack
        mov esp, stack_top
        call kernel_main

        hlt

