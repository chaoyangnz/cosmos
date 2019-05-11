/*
 * Processor registers for i386 and i486.
 */
#ifndef	_COSMOS_X86_PROC_REG_H_
#define	_COSMOS_X86_PROC_REG_H_

#include <compiler.h>
#include <stdint.h>
#include <kernel/segment.h>
#include "interrupt.h"

/*
 * CR0
 */
#define	CR0_PG	0x80000000		/*	 enable paging */
#define	CR0_CD	0x40000000		/* i486: cache disable */
#define	CR0_NW	0x20000000		/* i486: no write-through */
#define	CR0_AM	0x00040000		/* i486: alignment check mask */
#define	CR0_WP	0x00010000		/* i486: write-protect kernel access */
#define	CR0_NE	0x00000020		/* i486: handle numeric exceptions */
#define	CR0_ET	0x00000010		/*	 extension type is 80387 */

/*	 (not official) */
#define	CR0_TS	0x00000008		/*	 task switch */
#define	CR0_EM	0x00000004		/*	 emulate coprocessor */
#define	CR0_MP	0x00000002		/*	 monitor coprocessor */
#define	CR0_PE	0x00000001		/*	 enable protected mode */

/*
 * CR4
 */
#define CR4_VME	0x00000001		/* enable virtual intrs in v86 mode */
#define CR4_PVI	0x00000002		/* enable virtual intrs in pmode */
#define CR4_TSD	0x00000004		/* disable RDTSC in user mode */
#define CR4_DE	0x00000008		/* debug extensions (I/O breakpoints) */
#define CR4_PSE	0x00000010		/* page size extensions */
#define CR4_PAE	0x00000020		/* physical address extensions */
#define CR4_MCE	0x00000040		/* machine check exception */
#define CR4_PGE	0x00000080		/* page global extensions */
#define CR4_PCE	0x00000100		/* enable read perf counter instr */

extern unsigned get_eflags();
extern void set_eflags(unsigned eflags);
extern void cli();
extern void sti();
extern void cld();
extern void clts();
extern uint16_t get_cs();
#define set_cs(cs) \
    asm volatile("ljmp	%0,$1f \n " \
                 "1: \n" : : "i" (cs))
extern uint16_t get_ds();
extern void set_ds(uint16_t ds);
extern uint16_t get_es();
extern void set_es(uint16_t es);
extern uint16_t get_fs();
extern void set_fs(uint16_t fs);
extern uint16_t get_gs();
extern void set_gs(uint16_t gs);
extern uint16_t get_ss();
extern void set_ss(uint16_t ss);

extern uint32_t get_eax();
extern uint32_t get_ebx();
extern uint32_t get_ecx();
extern uint32_t get_edx();
extern uint32_t get_esi();
extern uint32_t get_edi();
extern uint32_t get_ebp();
extern uint32_t get_esp();
extern uint32_t get_eflags();
extern uint32_t get_eip();
extern uint32_t get_cr0();
extern void set_cr0(uint32_t value);


extern uint32_t get_eax();
extern uint32_t get_ebx();
extern uint32_t get_ecx();
extern uint32_t get_edx();
extern uint32_t get_esi();
extern uint32_t get_edi();
extern uint32_t get_ebp();
extern uint32_t get_esp();
extern uint32_t get_eflags();
extern uint32_t get_eip();
extern uint32_t get_cr0();
extern void set_cr0(uint32_t value);
extern uint32_t get_cr4();
extern void set_cr4(uint32_t value);
extern uint32_t get_msw();
extern uint32_t get_cr2();
extern uint32_t get_cr3();
extern void set_cr3(uint32_t value);
extern void set_ts();
extern void clear_ts();
extern uint16_t get_tr();
extern void set_tr(uint16_t seg);
extern void set_gdtr(gdt_desc_t gdt_desc);
extern gdt_desc_t get_gdtr();
extern void set_idt(idt_desc_t pseudo_desc);
extern uint16_t get_ldt();
extern void set_ldt(uint16_t seg);
extern uint32_t get_tsc();
extern uint32_t rdmsr(uint32_t msr);
extern void wrmsr(uint32_t msr, uint32_t high, uint32_t low);
extern void wrmsrll(uint32_t msr, uint32_t val);

#endif	/* _COSMOS_X86_PROC_REG_H_ */
