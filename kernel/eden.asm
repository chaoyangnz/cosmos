global start

extern multiboot__setup
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
        call multiboot__setup
        ;;;------------ENABLE SEGMENT--------------------
        ; setup GDT
        call .segment__setup

        ;;;------------PAGING SETUP--------------------
        ; setup paging
        call page__setup

        ;;;------------HAPPY WORLD--------------------
        ; set up stack
        mov esp, stack_top
        call kernel_main

        hlt

.segment__setup:
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
               ret

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
        stack_bottom: resb 4096               ; 4k
        stack_top:

