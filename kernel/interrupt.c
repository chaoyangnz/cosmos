#include <kernel/interrupt.h>

#include <kernel/segment.h>
#include <stdio.h>
#include "io.h"

#include "keyboard.h"

idt_t idt;

// https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller

void interrupt__fill_interrupt_descriptor(gate_descriptor_t *gate_desc, addr_t isr) {
    gate_desc->offset_low = isr & 0xffff;
    gate_desc->segment_selector = SEG_INDEX_KERNEL_CODE << 3;
    gate_desc->not_used = 0b00000;
    gate_desc->zero = 0b000;
    gate_desc->gate_type = GATE_TYPE_INTERRUPT;
    gate_desc->storage_segment = 0b0;
    gate_desc->dpl = 0b00;
    gate_desc->present = 0b1;
    gate_desc->offset_high = isr >> 16;
}

void interrupt__pic_remap() {
    // save masks
    uint8_t a1 = inb(PIC1_PORT_DATA);
    uint8_t a2 = inb(PIC2_PORT_DATA);

    outb(PIC1_PORT_COMMAND, 0x11); // ;restart PIC1
    outb(PIC2_PORT_COMMAND, 0x11); // ;restart PIC2

    outb(PIC1_PORT_DATA, PIC1_START_INTERRUPT); // ;PIC1 now starts at 32
    outb(PIC2_PORT_DATA, PIC2_START_INTERRUPT); // ;PIC2 now starts at 40

    // setup cascading
    outb(PIC1_PORT_DATA, 0x04); // tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC2_PORT_DATA, 0x02); // tell Slave PIC its cascade identity (0000 0010)

    // 8086/88 (MCS-80/85) mode
    outb(PIC1_PORT_DATA, 0x01);
    outb(PIC2_PORT_DATA, 0x01);

    // restore saved masks
    outb(PIC1_PORT_DATA, a1);
    outb(PIC2_PORT_DATA, a2);
}

void interrupt__pic_mask_irq(uint8_t irq) {
    if(irq > 15) return;

    if(irq < 8) {
        uint8_t data = inb(PIC1_PORT_DATA);
        data |= (1 << irq);
        outb(PIC1_PORT_DATA, data);
    } else {
        uint8_t data = inb(PIC2_PORT_DATA);
        data |= (1 << (irq - 8));
    }
}

void interrupt__pic_acknowledge(uint8_t irq) {
    outb(PIC1_PORT_COMMAND, PIC_ACK);
    if (irq > 8) {
        outb(PIC2_PORT_COMMAND, PIC_ACK);
    }
}

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

void interrupt__handler(interrupt_state state) {
    if(state.interrupt == INTERRUPT_KEYBOARD) {
        unsigned char scan_code = keyboard__read_scan_code();
        char ch = keyboard__scan_code_to_ascii(scan_code);
        if(ch > 0) {
            printf("keyboard: %c \n", ch);
        }
    }
    if(is_irq(state.interrupt)) {
        interrupt__pic_acknowledge(interrupt_to_irq(state.interrupt));
    }
}

typedef void *isr_t;

extern isr_t interrupt_handler_32;
extern isr_t interrupt_handler_33;
extern isr_t interrupt_handler_34;
extern isr_t interrupt_handler_35;
extern isr_t interrupt_handler_36;
extern isr_t interrupt_handler_37;
extern isr_t interrupt_handler_38;
extern isr_t interrupt_handler_39;
extern isr_t interrupt_handler_40;
extern isr_t interrupt_handler_41;
extern isr_t interrupt_handler_42;
extern isr_t interrupt_handler_43;
extern isr_t interrupt_handler_44;
extern isr_t interrupt_handler_45;
extern isr_t interrupt_handler_46;
extern isr_t interrupt_handler_47;


void interrupt__setup() {
    interrupt__pic_remap();

//    for(uint32_t i = 0; i < IDT_SIZE; ++i) {
//        if(i >= PIC1_START_INTERRUPT && i <= PIC2_END_INTERRUPT) continue;
//        interrupt__fill_interrupt_descriptor(&idt[i], &interrupt_handler_empty);
//    }

    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(0)], &interrupt_handler_32);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(1)], &interrupt_handler_33);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(2)], &interrupt_handler_34);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(3)], &interrupt_handler_35);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(4)], &interrupt_handler_36);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(5)], &interrupt_handler_37);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(6)], &interrupt_handler_38);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(7)], &interrupt_handler_39);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(8)], &interrupt_handler_40);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(9)], &interrupt_handler_41);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(10)], &interrupt_handler_42);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(11)], &interrupt_handler_43);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(12)], &interrupt_handler_44);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(13)], &interrupt_handler_45);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(14)], &interrupt_handler_46);
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(15)], &interrupt_handler_47);

    idt_desc_t idt_desc = {
        .base = (addr_t)&idt,
        .limit = IDT_SIZE * 8 - 1
    };
    set_idt(idt_desc);

//    asm ("int $33"); // test

    // enable keyboard
    outb(0x21,0xfd);
    outb(0xa1,0xff);
    sti();

    printf("IDT: %#x \n", &idt);
}

