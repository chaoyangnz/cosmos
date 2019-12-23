#include "interrupt.h"

#include <stdio.h>
#include "segment.h"
#include "io.h"
#include "register.h"
#include "drivers/keyboard.h"

idt_t idt;

// https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller

static void interrupt__fill_interrupt_descriptor(gate_descriptor_t *gate_desc, addr_t isr) {
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

static void interrupt__pic_remap() {
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

static void interrupt__pic_mask_irq(uint8_t irq) {
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

static void interrupt__pic_acknowledge(uint8_t irq) {
    outb(PIC1_PORT_COMMAND, PIC_ACK);
    if (irq > 8) {
        outb(PIC2_PORT_COMMAND, PIC_ACK);
    }
}

void interrupt__setup() {
    interrupt__pic_remap();

//    for(uint32_t i = 0; i < IDT_SIZE; ++i) {
//        if(i >= PIC1_START_INTERRUPT && i <= PIC2_END_INTERRUPT) continue;
//        interrupt__fill_interrupt_descriptor(&idt[i], addr(isrempty);
//    }

    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(0)], addr(isr32));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(1)], addr(isr33));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(2)], addr(isr34));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(3)], addr(isr35));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(4)], addr(isr36));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(5)], addr(isr37));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(6)], addr(isr38));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(7)], addr(isr39));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(8)], addr(isr40));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(9)], addr(isr41));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(10)], addr(isr42));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(11)], addr(isr43));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(12)], addr(isr44));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(13)], addr(isr45));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(14)], addr(isr46));
    interrupt__fill_interrupt_descriptor(&idt[irq_to_interrupt(15)], addr(isr47));

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

// used by interrupt service routines in interrupt.asm
extern void interrupt__handler(interrupt_state state) {
    if(state.interrupt == INTERRUPT_KEYBOARD) {
        keyboard__driver();
    }
    if(is_irq(state.interrupt)) {
        interrupt__pic_acknowledge(interrupt_to_irq(state.interrupt));
    }
}

