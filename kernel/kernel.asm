global start

RED         equ 0x04
VGA_BASE    equ 0xb8000
VGA_SIZE    equ 80 * 25                         ; console size

section .text
bits 32
start:
        mov ebx, VGA_BASE                       ; VGA area base

        ; Clear screen
        call clear

        ; Print
        mov esi, msg
        call print

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