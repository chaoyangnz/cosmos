global start
global page_directory
global page_tables

extern page__setup
extern kernel_main

KERNEL_BASE equ 0xC0000000

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
        ;; !! DON'T USE ebx which is holding the multiboot info
        ;;;------------ENABLE SEGMENT--------------------
        ; setup GDT
        mov eax, boot_gdt_desc
        lgdt [eax]

        jmp	0x08:.cs_loaded ; long jump to reload cs
.cs_loaded:
        mov ax, 0x10
        mov ds, ax   ; ds -> kernel data
        mov es, ax   ; es -> kernel data
        mov ss, ax   ; ss -> kernel code
        mov ax, 0
        mov fs, ax   ; fs -> null seg
        mov gs, ax   ; gs -> null seg

        ;;;------------PAGE DIRECTORY--------------------
        ;;; setup initial blank page directories (all page table pages present)
        ;;; setup mapped page table (16M: including frame buffer 0xb8000 )
        call page__setup

        ;;;------------ENABLE PAGING--------------------
        ;;; enable paging
        mov eax, page_directory - KERNEL_BASE
        mov cr3, eax

        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax

        ;;;------------HAPPY WORLD--------------------
        ; set up stack
        mov esp, stack_top
        call kernel_main

        hlt


section .boot_data
align 4
        boot_gdt_desc:
                db 3 * 8 - 1, 0x00
                dd boot_gdt

        boot_gdt:
                dq 0 ; seg_null
                db 0xff, 0xff, 0x00, 0x00, 0x00, 0x9a, 0xcf, 0x00 ; seg_kernel_code
                db 0xff, 0xff, 0x00, 0x00, 0x00, 0x93, 0xcf, 0x00 ; seg_kernel_data

section .bss
align 0x1000
        page_directory: ; 4K
            resd 1024
        page_tables:  ; 4K * 1024 = 4M
            times 1024 resd 1024 ; 1024 tables, each table has 1024 entry x 4 bytes
        stack_bottom: resb 4096               ; 4k
        stack_top:

