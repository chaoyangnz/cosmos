#ifndef COSMOS_INTERRUPT_H
#define COSMOS_INTERRUPT_H

#include <compiler.h>
#include <stdint.h>


/* The base environment provides a full-size 256-entry IDT.
   This is needed, for example, under VCPI or Intel MP Standard PCs.  */
#define IDT_SIZE	256

#define GATE_TYPE_TASK 0b0101
#define GATE_TYPE_INTERRUPT_16 0b0110
#define GATE_TYPE_TRAP_16  0b0111
#define GATE_TYPE_INTERRUPT 0b1110 // 32 bit
#define GATE_TYPE_TRAP 0b1111       // 32 bit */


typedef struct {
    uint32_t	offset_low      :16,	/* irq address 0..15 */
                segment_selector        :16,
                not_used        :5,    // 00000
                zero            :3,    // 000
                gate_type       :4,
                storage_segment :1,
                dpl             :2,
                present         :1,
                offset_high     :16;	/* irq address 16..31 */
} gate_descriptor_t;

typedef gate_descriptor_t idt_t[IDT_SIZE];

extern idt_t idt;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} PACKED idt_desc_t;

#define IRQ_START 0
#define IRQ_END 15

#define PIC1_START_INTERRUPT 32  // irq0
#define PIC1_END_INTERRUPT   39  // irq7
#define PIC2_START_INTERRUPT 40  // irq8
#define PIC2_END_INTERRUPT   47  // irq15

#define is_irq(interrupt) (interrupt >= PIC1_START_INTERRUPT && interrupt <= PIC2_END_INTERRUPT)
#define irq_to_interrupt(irq) (irq + PIC1_START_INTERRUPT)
#define interrupt_to_irq(interrupt) (interrupt - PIC1_START_INTERRUPT)

#define PIC1_PORT_COMMAND 0x20
#define PIC2_PORT_COMMAND 0xA0
#define PIC1_PORT_DATA    0x21
#define PIC2_PORT_DATA    0xA1

#define INTERRUPT_KEYBOARD PIC1_START_INTERRUPT + 1

#define PIC_ACK     0x20 /* End-of-interrupt command code */

typedef void *isr_t;

typedef struct interrupt_state {
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
    uint32_t esp;
    uint32_t interrupt;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed)) interrupt_state;

// --- these interrupt service routines are defined in interrupt.asm
// PIC1
extern isr_t isr32;
extern isr_t isr33;
extern isr_t isr34;
extern isr_t isr35;
extern isr_t isr36;
extern isr_t isr37;
extern isr_t isr38;
extern isr_t isr39;
// PIC2
extern isr_t isr40;
extern isr_t isr41;
extern isr_t isr42;
extern isr_t isr43;
extern isr_t isr44;
extern isr_t isr45;
extern isr_t isr46;
extern isr_t isr47;

extern void interrupt__setup();

#endif //COSMOS_INTERRUPT_H
