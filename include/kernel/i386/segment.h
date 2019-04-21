#ifndef	_X86_SEG_H_
#define	_X86_SEG_H_


/*
 * x86 segmentation.
 */

/*
 * Real segment descriptor.
 */
struct segment_descriptor {
    unsigned int	limit_low:16,	/* size 0..15 */
            base_low:16,	/* base  0..15 */
            base_med:8,	/* base  16..23 */
            access:8,	/* access byte */
            limit_high:4,	/* size 16..19 */
            granularity:4,	/* granularity */
            base_high:8;	/* base 24..31 */
};

/*
 * Trap, interrupt, or call gate.
 */
struct x86_gate {
    unsigned int	offset_low:16,	/* gdt_address 0..15 */
            selector:16,
            word_count:8,
            access:8,
            offset_high:16;	/* gdt_address 16..31 */
};


#define	SZ_32		0x4			/* 32-bit segment */
#define SZ_16		0x0			/* 16-bit segment */
#define	SZ_G		0x8			/* 4K limit field */

#define	ACC_A		0x01			/* accessed */
#define	ACC_TYPE	0x1e			/* type field: */

#define	ACC_TYPE_SYSTEM	0x00			/* system descriptors: */

#define	ACC_LDT		0x02			    /* LDT */
#define	ACC_CALL_GATE_16 0x04			    /* 16-bit call gate */
#define	ACC_TASK_GATE	0x05			    /* task gate */
#define	ACC_TSS		0x09			    /* task segment */
#define	ACC_CALL_GATE	0x0c			    /* call gate */
#define	ACC_INTR_GATE	0x0e			    /* interrupt gate */
#define	ACC_TRAP_GATE	0x0f			    /* trap gate */

#define	ACC_TSS_BUSY	0x02			    /* task busy */

#define	ACC_TYPE_USER	0x10			/* user descriptors */

#define	ACC_DATA	0x10			    /* data */
#define	ACC_DATA_W	0x12			    /* data, writable */
#define	ACC_DATA_E	0x14			    /* data, expand-down */
#define	ACC_DATA_EW	0x16			    /* data, expand-down, writable */

#define	ACC_CODE	0x18			    /* code */
#define	ACC_CODE_R	0x1a			    /* code, readable */
#define	ACC_CODE_C	0x1c			    /* code, conforming */
#define	ACC_CODE_CR	0x1e			    /* code, conforming, readable */

#define	ACC_PL		0x60			/* access rights: */
#define	ACC_PL_K	0x00			/* kernel access only */
#define	ACC_PL_U	0x60			/* user access */
#define	ACC_P		0x80			/* segment present */

/*
 * Components of a selector
 */
#define	SEL_LDT		0x04			/* local selector */
#define	SEL_PL		0x03			/* privilege level: */
#define	SEL_PL_K	0x00			    /* kernel selector */
#define	SEL_PL_U	0x03			    /* user selector */

/*
 * Convert selector to descriptor table index.
 */
#define	sel_idx(sel)	((sel)>>3)

#include <compiler.h>

/* Return the privilege level of a segment selector */
#define ISPL(s)         ((s) & SEL_PL)

#define USERMODE(s, f)          (ISPL(s) == SEL_PL_U || ((f) & EFL_VM) != 0)
#define KERNELMODE(s, f)        (ISPL(s) == SEL_PL_K && ((f) & EFL_VM) == 0)


/* Format of a "gdt-descriptor", used for loading the IDT and GDT.  */
struct gdt_descriptor
{
    short pad;
    unsigned short limit;
    unsigned int base;
};

inline void
fill_segment_descriptor(struct segment_descriptor *desc, unsigned base, unsigned limit,
                        unsigned char access, unsigned char sizebits);
inline void
fill_descriptor_base(struct segment_descriptor *desc, unsigned base);
inline void
fill_descriptor_limit(struct segment_descriptor *desc, unsigned limit);
inline void
fill_gate(struct x86_gate *gate, unsigned offset, unsigned short selector,
          unsigned char access, unsigned char word_count);

#define NULL_SEGMENT  0x00
#define KERNEL_CODE	0x08
#define KERNEL_DATA	0x10	/* Kernel's PL0 code segment */
#define USER_CODE	0x18	/* Kernel's PL0 data segment */
#define USER_DATA	0x20	/* 16-bit version of KERNEL_CS */

/* Leave a little additional room beyond this for customization */
#define GDT_SIZE		(0x28/8) /* 5 GTP entries */


extern struct segment_descriptor gdt[];

/* Initialize the base GDT descriptors with sensible defaults.  */
extern void gdt_init(void);

/* Load the base GDT into the CPU.  */
extern void gdt_load(void);

/* Fill a segment descriptor.  */
inline void
fill_segment_descriptor(struct segment_descriptor *desc, unsigned base, unsigned limit,
                        unsigned char access, unsigned char sizebits)
{
    if (limit > 0xfffff)
    {
        limit >>= 12;
        sizebits |= SZ_G;
    }
    desc->limit_low = limit & 0xffff;
    desc->base_low = base & 0xffff;
    desc->base_med = (base >> 16) & 0xff;
    desc->access = access | ACC_P;
    desc->limit_high = limit >> 16;
    desc->granularity = sizebits;
    desc->base_high = base >> 24;
}

/* Set the base address in a segment descriptor.  */
//inline void
//fill_descriptor_base(struct segment_descriptor *desc, unsigned base)
//{
//    desc->base_low = base & 0xffff;
//    desc->base_med = (base >> 16) & 0xff;
//    desc->base_high = base >> 24;
//}
//
/* Set the size in a segment descriptor.  */
//inline void
//fill_descriptor_limit(struct segment_descriptor *desc, unsigned limit)
//{
//    if (limit > 0xfffff)
//    {
//        limit >>= 12;
//        desc->granularity |= SZ_G;
//    }
//    else
//        desc->granularity &= ~SZ_G;
//    desc->limit_low = limit & 0xffff;
//    desc->limit_high = limit >> 16;
//}

/* Fill a gate with particular values.  */
inline void
fill_gate(struct x86_gate *gate, unsigned offset, unsigned short selector,
          unsigned char access, unsigned char word_count)
{
    gate->offset_low = offset & 0xffff;
    gate->selector = selector;
    gate->word_count = word_count;
    gate->access = access | ACC_P;
    gate->offset_high = (offset >> 16) & 0xffff;
}

#endif	/* _X86_SEG_H_ */
