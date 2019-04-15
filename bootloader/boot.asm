org 0x7C00                              ; BIOS loads our program at this address
use16

BOOT_SIGNATURE equ 0xAA55               ; bootable signature 0x55 0xAA

section .text

start:
            mov esp, stack_top          ; setup a stack
            cli
            mov si, msg
            call print
            hlt

print:
            mov ah, 0x0E                ; indicate BIOS int10h to write a char at AL
.next       lodsb                       ; load SI into AL and increment SI
            test al, al                 ; test if char is the end of string
            jz .end
            int 0x10                    ; int 0x10 for teleport output
            jmp .next
.end        ret

TEXT_LEN equ $ - $$
 
section .data align=1
    msg db "Hello, World!", 0
    stack_bottom: times 510 - TEXT_LEN - ($ - $$) db '@'
    stack_top:
    dw BOOT_SIGNATURE                   ; Boot Signature


