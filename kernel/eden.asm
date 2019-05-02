global start
extern kernel_main
extern page_directory
extern page_tables

PHYSICAL_START equ 0x0
VIRTUAL_START equ 0xC0000000

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
        ;;; setup initial blank page directories (not present)
        mov esi, page_tables
        or esi, 0x00000002       ; not present bit
        mov ecx, 0          ; 0 - 1023
.pde:   mov [page_directory + ecx * 4], esi
        inc ecx
        add esi, 4096
        cmp ecx, 1024
        jl .pde

        ;;;------------PAGE TABLE--------------------
        ;;; setup identity mapping page table (4M: 0x000000~0x400000 -> 0x000000 ~ 0x400000 including frame buffer 0xb8000 )
        mov ecx, 0
        call map_page_table

        mov ecx, 1
        call map_page_table

        ;;; setup kernel page table (4M: 0xC0000000~0xC0400000 -> 0x000000 ~ 0x400000 including frame buffer 0xb8000 )
        mov ecx, 768
        call map_page_table

        ;;; setup kernel page table (4M: 0xC0400000~0xC0800000 -> 0xC0400000 ~ 0x800000 including frame buffer 0xb8000 )
        mov ecx, 769
        call map_page_table

        ;;;------------ENABLE PAGING--------------------
        ;;; enable paging
        mov eax, page_directory
        mov cr3, eax

        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax

        ; recycle identity mapping of lower 4M
        mov eax, cr3
        mov dword [eax + 0 * 4], 0x00000002
        mov dword [eax + 1 * 4], 0x00000002

        ;;;------------HAPPY WORLD--------------------
        ; set up stack
        mov esp, stack_top
        call kernel_main

        hlt

; ecx: index in page directory
map_page_table:
        ; calculate page table address by index
        mov edi, page_tables ; page_tables + cx * 4096
        mov edx, ecx
        imul edx, 4096
        add edi, edx

        ; set present in page directory
        mov edx, edi
        or edx, 0x00000003
        mov [page_directory + ecx * 4], edx

        ; calculate physical address to map
        mov esi, PHYSICAL_START
        mov edx, ecx
        cmp edx, 768
        jl .1
        sub edx, 768
    .1: imul edx, 0x400000  ; PHYSICAL_START + ecx x 4M
        add esi, edx

        ;;;;;; fill every entry in a page table
        or esi, 0x00000003
        mov ecx, 0
;
  .pte: mov [edi + ecx * 4], esi
        add esi, 4096
        inc ecx
        cmp ecx, 1024
        jl .pte
        ret

section .boot_bss
align 0x1000
        page_directory: ; 4K
            resd 1024
        page_tables:  ; 4K * 1024 = 4M
            times 1024 resd 1024 ; 1024 tables, each table has 1024 entry x 4 bytes

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

