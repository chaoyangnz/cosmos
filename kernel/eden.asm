global start
extern kernel_main

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
        mov edi, boot_page_directory
        ;;; setup initial blank page directories (not present)
        mov esi, boot_page_table_blank
        or esi, 0x002       ; not present bit
        mov ecx, 0          ; 0 - 1023
.pde:   mov [edi + ecx * 4], esi
        inc ecx
        cmp ecx, 1024
        jl .pde

        ;;; put identity mapping page table of low 4M memory
        mov esi, boot_page_table_0
        or esi, 0x003
        mov [edi + 0], esi
        ;;; put page table of higher half 4M memory: 0xC0100000 << 22 = 768 (0x300)
        mov esi, boot_page_table_768
        or esi, 0x003
        mov [edi + 0x300 * 4], esi


        ;;;------------PAGE TABLE--------------------
        ;;; setup identity mapping page table (4M: 0x000000~0x400000 -> 0x000000 ~ 0x400000 including frame buffer 0xb8000 )
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

        ;;; setup kernel page table (4M: 0xC0000000~0xC0400000 -> 0x000000 ~ 0x400000 including frame buffer 0xb8000 )
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

        ;;;------------ENABLE PAGING--------------------
        ;;; enable paging
        mov eax, boot_page_directory
        mov cr3, eax

        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax

        ; recycle identity mapping of lower 4M
        mov eax, cr3
        mov dword [eax], 0x00000002

        ;;;------------HAPPY WORLD--------------------
        ; set up stack
        mov esp, stack_top
        call kernel_main

        hlt

section .boot_bss
align 0x1000
        boot_page_directory: resd 1024
        boot_page_table_blank: resd 1024
        boot_page_table_0: resd 1024
        boot_page_table_768: resd 1024

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

