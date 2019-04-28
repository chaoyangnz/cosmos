global start
extern kernel_main

PHYSICAL_START equ 0x0
VIRTUAL_START equ 0xC0000000

extern kernel_virtual_end
extern kernel_physical_end

MULTIBOOT_PAGE_ALIGN    equ     1<<0
MULTIBOOT_MEMORY_INFO   equ     1<<1
MULTIBOOT_VIDEO_MODE    equ     1<<2
MULTIBOOT_INFO_FRAMEBUFFER_INFO  equ       0x00001000
MULTIBOOT_INFO_MEM_MAP  equ     0x00000040
MULTIBOOT_FLAGS         equ     MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_INFO_MEM_MAP | MULTIBOOT_VIDEO_MODE | MULTIBOOT_INFO_FRAMEBUFFER_INFO
MULTIBOOT_MAGIC         equ     0x1BADB002
MULTIBOOT_CHECKSUM      equ     -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

RED         equ 0x04
VGA_BASE    equ 0xb8000                         ; VGA area base
VGA_SIZE    equ 80 * 25                         ; console size

section .boot
bits 32
align 0x1000
multiboot:
    dd MULTIBOOT_MAGIC                                ; magic number (multiboot 2)
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM
start:
        ; setup GDT
        mov eax, gdt_desc
        lgdt [eax]

        jmp	0x08:.cs_loaded
.cs_loaded:
        mov dx, 0x10
        mov ds, dx
        mov es, dx
        mov ss, dx
        mov dx, 0
        mov fs, dx
        mov gs, dx

        ; setup kernel page directory
        mov edi, boot_page_directory
        mov esi, 0x00000002 ; not present
        mov ecx, 0
        ; set all page tables not present
.pde:   mov [edi + ecx * 4], esi
        inc ecx
        cmp ecx, 1024
        jl .pde

        ; identity mapping
        mov esi, boot_page_table_0
        or esi, 0x003
        mov [edi], esi
        ; kernel page table to directory
        mov esi, boot_page_table_768
        or esi, 0x003
        mov [edi + 0x300 * 4], esi


        ; setup identity mapping page table (4M: 0x000000~0x400000 -> 0x000000 ~ 0x400000 including frame buffer 0xb8000 )
        mov edi, boot_page_table_0
        mov esi, PHYSICAL_START
        or esi, 0x003
        mov ecx, 0
.pte_0:
        mov [edi + ecx * 4], esi
        add esi, 4096
        inc ecx
        cmp ecx, 1024
        jl .pte_0

        ; setup kernel page table (4M: 0xC0000000~0xC0400000 -> 0x000000 ~ 0x400000 including frame buffer 0xb8000 )
        mov edi, boot_page_table_768
        mov esi, PHYSICAL_START
        or esi, 0x003
        mov ecx, 0
.pte_768:
        mov [edi + ecx * 4], esi
        add esi, 4096
        inc ecx
        cmp ecx, 1024
        jl .pte_768

        ; enable paging
        mov eax, boot_page_directory
        mov cr3, eax

        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax

.after_page_enabled:
        ; set up stack
        mov esp, stack_top
        call kernel_main

        hlt

section .boot_data
align 0x1000
        boot_page_directory: times 4096 db 0
        boot_page_table_0: times 4096 db 0
        boot_page_table_768: times 4096 db 0

        gdt_desc:
                db 0x27, 0x00
                dd gdt

        gdt:
        seg_null: dq 0
        seg_kernel_code: db 0xff, 0xff, 0x00, 0x00, 0x00, 0x9a, 0xcf, 0x00
        seg_kernel_data: db 0xff, 0xff, 0x00, 0x00, 0x00, 0x93, 0xcf, 0x00
        seg_user_code:   db 0xff, 0xff, 0x00, 0x00, 0x00, 0xfa, 0xcf, 0x00
        seg_user_data:   db 0xff, 0xff, 0x00, 0x00, 0x00, 0xf2, 0xcf, 0x00

section .bss
        stack_bottom: resb 4096               ; 4k
        stack_top:

