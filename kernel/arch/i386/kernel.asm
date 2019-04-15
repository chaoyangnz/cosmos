global start
extern kernel_main

RED         equ 0x04
VGA_BASE    equ 0xb8000                         ; VGA area base
VGA_SIZE    equ 80 * 25                         ; console size

section .text
bits 32
start:
        ;The bootloader has loaded us into 32-bit protected mode on a x86
        ;machine. Interrupts are disabled. Paging is disabled. The processor
        ;state is as defined in the multiboot standard. The kernel has full
        ;control of the CPU. The kernel can only make use of hardware features
        ;and any code it provides as part of itself. There's no printf
        ;function, unless the kernel provides its own <stdio.h> header and a
        ;printf implementation. There are no security restrictions, no
        ;safeguards, no debugging mechanisms, only what the kernel provides
        ;itself. It has absolute and complete power over the
        ;machine.

        ; set up stack
        mov esp, stack_top

        ; Clear screen
        call clear

        ; Print hello
        mov esi, msg
        call print

        call kernel_main

        hlt

clear:
        mov ecx, VGA_SIZE ;
        mov dx, 0x0020                         ;  space symbol (0x20) on black background
.next   mov [VGA_BASE + ecx * 2], dx
        dec ecx
        cmp ecx, -1
        jnz clear.next
        ret

print:
        mov ecx, 0
.next   mov al, [esi + ecx]
        test al, al
        jz print.end
        mov ah, RED
        mov [VGA_BASE + ecx * 2], ax
        inc ecx
        jmp print.next
.end    ret

section .data
    msg db 'Hello, World!', 0

section .bss
align 16
    stack_bottom: resb 16384                    ; 16k
    stack_top: