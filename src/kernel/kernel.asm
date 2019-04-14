global start

COLOR equ 0x2A

section .text
bits 32
start:
    ; print `Hello,world` to screen
    msg db 'H', COLOR, 'e', COLOR           ; he
    mov EAX, [msg]
    mov dword [0xb8000], EAX

    mov dword [0xb8000 + 4], 0x2A6c2A6c     ; ll
    mov dword [0xb8000 + 8], 0x2A2c2A6f     ; o,
    mov dword [0xb8000 + 12], 0x2A6f2A77    ; wo
    mov dword [0xb8000 + 16], 0x2A6c2A72    ; rl
    mov dword [0xb8000 + 20], 0x2A212A64    ; d!

    hlt
