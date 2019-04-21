;global set_gdt
;global set_cs

gdtr:
    DW 0 ; For limit storage
    DD 0 ; For base storage

;set_gdt: ; base_addr, size
;   MOV   EAX, [esp + 4]   ; base_address => EAX
;   MOV   [gdtr + 2], EAX  ;
;   MOV   AX, [ESP + 8]    ;
;   MOV   [gdtr], AX
;   LGDT  [gdtr]
;   RET

;set_cs:
;   jmp dword 0x08:.next
;   .next:
;   ret