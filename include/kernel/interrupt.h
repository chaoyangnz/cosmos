#ifndef _COSMOS_INTERRUPT_H_
#define _COSMOS_INTERRUPT_H_

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

extern void interrupt__setup();
extern void interrupt__fill_interrupt_descriptor(gate_descriptor_t *gate_desc, uint32_t isr);
extern void interrupt__load_idt();

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

#endif /* _COSMOS_INTERRUPT_H_ */
