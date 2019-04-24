#ifndef	_COSMOS_X86_SEG_H_
#define	_COSMOS_X86_SEG_H_


#include <stdint.h>
#include <compiler.h>

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


/* Return the privilege level of a segment selector */
#define ISPL(s)         ((s) & SEL_PL)

#define USERMODE(s, f)          (ISPL(s) == SEL_PL_U || ((f) & EFL_VM) != 0)
#define KERNELMODE(s, f)        (ISPL(s) == SEL_PL_K && ((f) & EFL_VM) == 0)

#define SEG_INDEX_NULL          0x00
#define SEG_INDEX_KERNEL_CODE	0x01
#define SEG_INDEX_KERNEL_DATA	0x02	/* Kernel's PL0 code segment */
#define SEG_INDEX_USER_CODE	    0x03	/* Kernel's PL0 data segment */
#define SEG_INDEX_USER_DATA 	0x04	/* 16-bit version of KERNEL_CS */

typedef struct  segment_selector_t {
    uint16_t rpl                 :2,
             table_indicator     :1,
             index               :13
} segment_selector_t;

#define segment_selector(index, table_indicator, rpl) \
    ((index) << 3 | (table_indicator) << 2 | rpl)


/* Leave a little additional room beyond this for customization */
#define GDT_SIZE		(0x28/8) /* 5 GTP entries */


typedef struct segment_descriptor_t {
    uint32_t	limit_low       :16,	/* size 0..15 */
                base_low        :16,	/* base  0..15 */
                base_med        :8,	/* base  16..23 */
                access          :8,	/* access byte */
                limit_high      :4,	/* size 16..19 */
                granularity     :4,	/* granularity */
                base_high       :8;	/* base 24..31 */
} segment_descriptor_t;

/*
 * Trap, interrupt, or call gate.
 */
typedef struct x86_gate_t {
    uint32_t	offset_low      :16,	/* gdt_address 0..15 */
                selector        :16,
                word_count      :8,
                access          :8,
                offset_high     :16;	/* gdt_address 16..31 */
} x86_gate_t;

/* Format of a "gdt-descriptor", used for loading the IDT and GDT.  */
typedef struct
{
    uint16_t limit;
    uint32_t base;
} PACKED gdt_desc_t;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} PACKED idt_desc_t;

extern segment_descriptor_t gdt[GDT_SIZE];

extern void fill_segment_descriptor(segment_descriptor_t *desc, uint32_t base, uint32_t limit, uint8_t access, uint8_t sizebits);
extern void fill_descriptor_base(segment_descriptor_t *desc, uint32_t base);
extern void fill_descriptor_limit(segment_descriptor_t *desc, uint32_t limit);
extern void fill_gate(x86_gate_t *gate, uint32_t offset, uint16_t selector, uint8_t access, uint8_t word_count);

/* Initialize the base GDT descriptors with sensible defaults.  */
extern void gdt_init(void);

/* Load the base GDT into the CPU.  */
extern void gdt_load(void);



#endif	/* _COSMOS_X86_SEG_H_ */
