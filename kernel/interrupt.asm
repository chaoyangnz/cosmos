extern interrupt__handler

%macro interrupt_handler_without_error_code 1
    global interrupt_handler_%1
    interrupt_handler_%1:
        push    dword 0                     ; push 0 as error code
        push    dword %1                    ; push the interrupt number
        jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro interrupt_handler_with_error_code 1
    global interrupt_handler_%1
    interrupt_handler_%1:
        push    dword %1                    ; push the interrupt number
        jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

common_interrupt_handler:               ; the common parts of the generic interrupt handler
        ; save the registers
        pusha

        ; call the C function
        call    interrupt__handler

        ; restore the registers
        popa

        ; return to the code that got interrupted
        iret

global interrupt_handler_empty
interrupt_handler_empty:
        iret

interrupt_handler_without_error_code 32 ; irq0
interrupt_handler_without_error_code 33 ; irq1
interrupt_handler_without_error_code 34 ; irq2
interrupt_handler_without_error_code 35 ; irq3
interrupt_handler_without_error_code 36 ; irq4
interrupt_handler_without_error_code 37 ; irq5
interrupt_handler_without_error_code 38 ; irq6
interrupt_handler_without_error_code 39 ; irq7
interrupt_handler_without_error_code 40 ; irq8
interrupt_handler_without_error_code 41 ; irq9
interrupt_handler_without_error_code 42 ; irq10
interrupt_handler_without_error_code 43 ; irq11
interrupt_handler_without_error_code 44 ; irq12
interrupt_handler_without_error_code 45 ; irq13
interrupt_handler_without_error_code 46 ; irq14
interrupt_handler_without_error_code 47 ; irq15

