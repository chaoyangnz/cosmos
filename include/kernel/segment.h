#ifndef	_COSMOS_X86_SEG_H_
#define	_COSMOS_X86_SEG_H_


#include <stdint.h>
#include <compiler.h>

#define	SEG_SZ_32		0x4			        /* 32-bit segment */
#define SEG_SZ_16		0x0			        /* 16-bit segment */
#define	SEG_SZ_GRANULARITY		0x8			/* 4K limit field */

#define	SEG_DESC_ACC_A		0x01			/* accessed */
#define	SEG_DESC_ACC_TYPE	0x1e			/* type field: */

#define	SEG_DESC_ACC_TYPE_SYSTEM	0x00			/* system descriptors: */

#define	SEG_DESC_ACC_LDT		0x02			    /* LDT */
#define	SEG_DESC_ACC_CALL_GATE_16 0x04			    /* 16-bit call gate */
#define	SEG_DESC_ACC_TASK_GATE	0x05			    /* task gate */
#define	SEG_DESC_ACC_TSS		0x09			    /* task segment */
#define	SEG_DESC_ACC_CALL_GATE	0x0c			    /* call gate */
#define	SEG_DESC_ACC_INTR_GATE	0x0e			    /* interrupt gate */
#define	SEG_DESC_ACC_TRAP_GATE	0x0f			    /* trap gate */

#define	SEG_DESC_ACC_TSS_BUSY	0x02			    /* task busy */

#define	SEG_DESC_ACC_TYPE_USER	0x10			/* user descriptors */

#define	SEG_DESC_ACC_DATA	0x10			    /* data */
#define	SEG_DESC_ACC_DATA_W	0x12			    /* data, writable */
#define	SEG_DESC_ACC_DATA_E	0x14			    /* data, expand-down */
#define	SEG_DESC_ACC_DATA_EW	0x16			/* data, expand-down, writable */

#define	SEG_DESC_ACC_CODE	0x18			    /* code */
#define	SEG_DESC_ACC_CODE_R	0x1a			    /* code, readable */
#define	SEG_DESC_ACC_CODE_C	0x1c			    /* code, conforming */
#define	SEG_DESC_ACC_CODE_CR	0x1e			/* code, conforming, readable */

#define	SEG_DESC_ACC_PL		0x60			/* access rights: */
#define	SEG_DESC_ACC_PL_K	0x00			/* kernel access only */
#define	SEG_DESC_ACC_PL_U	0x60			/* user access */
#define	SEG_DESC_ACC_P		0x80			/* segment present */

/*
 * Components of a selector
 */
#define	SEG_SEL_LDT		0x04			    /* local selector */
#define	SEG_SEL_PL		0x03			    /* privilege level: */
#define	SEG_SEL_PL_K	0x00			    /* kernel selector */
#define	SEG_SEL_PL_U	0x03			    /* user selector */

/*
 * Convert selector to descriptor table index.
 */
#define	sel_idx(sel)	((sel)>>3)


/* Return the privilege level of a segment selector */
#define ISPL(s)         ((s) & SEG_SEL_PL)

#define USERMODE(s, f)          (ISPL(s) == SEG_SEL_PL_U || ((f) & EFL_VM) != 0)
#define KERNELMODE(s, f)        (ISPL(s) == SEG_SEL_PL_K && ((f) & EFL_VM) == 0)

#define SEG_INDEX_NULL          0x00
#define SEG_INDEX_KERNEL_CODE	0x01
#define SEG_INDEX_KERNEL_DATA	0x02	/* Kernel's PL0 code segment */
#define SEG_INDEX_USER_CODE	    0x03	/* Kernel's PL0 data segment */
#define SEG_INDEX_USER_DATA 	0x04	/* 16-bit version of KERNEL_CS */

typedef struct {
    uint16_t rpl                 :2,
             table_indicator     :1,
             index               :13
} segment_selector_t;

#define segment_selector(index, table_indicator, rpl) \
    ((index) << 3 | (table_indicator) << 2 | rpl)


/* Leave a little additional room beyond this for customization */
#define GDT_SIZE		(0x28/8) /* 5 GTP entries */


typedef struct {
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
typedef struct {
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

typedef segment_descriptor_t gdt_t[GDT_SIZE];
extern gdt_t gdt;


/* Initialize the base GDT descriptors with sensible defaults.  */
extern void segment__setup(void);

/* Load the base GDT into the CPU.  */
extern void segment__load_gdt(void);
extern void segment__info();



#endif	/* _COSMOS_X86_SEG_H_ */
