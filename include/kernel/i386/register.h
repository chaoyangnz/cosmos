/*
 * Processor registers for i386 and i486.
 */
#ifndef	_COSMOS_X86_PROC_REG_H_
#define	_COSMOS_X86_PROC_REG_H_

#include <compiler.h>
#include <stdint.h>

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

inline unsigned get_eflags();
inline void set_eflags(unsigned eflags);
inline void cli();
inline void sti();
inline void cld();
#ifndef __cplusplus
inline void std();
#endif
inline void clts();
inline uint16_t get_cs();
inline uint16_t get_ds();
#define set_cs(cs) \
    asm volatile("ljmp	%0,$1f \n " \
                 "1: \n" : : "i" (cs))

inline void set_ds(uint16_t ds);
inline uint16_t get_es();
inline void set_es(uint16_t es);
inline uint16_t get_fs();
inline void set_fs(uint16_t fs);
inline uint16_t get_gs();
inline void set_gs(uint16_t gs);
inline uint16_t get_ss();
inline void set_ss(uint16_t ss);

/* Some processors, notably my Am386DX/40,
   seem to have some rather subtle pipeline- or timing-related bugs
   which case really weird things to happen with pushf's and popf's
   that come too close together...  */
#if 1
/* Look for the ``Intel inside'' label...
   For whatever bizzare reason, using the jmp-next-instruction hack
   sometimes causes a trap 15 to occur on the popfl instruction on a
   Pentium Pro 200.  Maybe the pushf's and popf's are too far apart...  */
inline unsigned get_eflags()
{
    unsigned eflags;
    asm volatile(
    "	pushfl\n"
    "	popl %0" : "=r" (eflags));
    return eflags;
}

inline void set_eflags(unsigned eflags)
{
    asm volatile(
    "	pushl %0\n"
    "	popfl" : : "r" (eflags));
}
#else
inline unsigned get_eflags()
{
	unsigned eflags;
	asm volatile(
	"	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	pushfl\n"
	"	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	popl %0" : "=r" (eflags));
	return eflags;
}

inline void set_eflags(unsigned eflags)
{
	asm volatile(
	"	pushl %0\n"
	"	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	popfl\n"
	"	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	jmp	1f\n"
	"1:	" : : "r" (eflags));
}
#endif

inline void cli() { asm("cli"); }
inline void sti() { asm("sti"); }
inline void cld() { asm("cld"); }
inline void clts() { asm("clts"); }

inline uint16_t get_cs()
{
    uint16_t cs;
    asm volatile("movw %%cs,%w0" : "=r" (cs));
    return cs;
}

inline uint16_t get_ds()
{
    uint16_t ds;
    asm volatile("movw %%ds,%w0" : "=r" (ds));
    return ds;
}
inline void set_ds(uint16_t ds)
{
    asm volatile("movw %w0,%%ds" : : "r" (ds));
}

inline uint16_t get_es()
{
    uint16_t es;
    asm volatile("movw %%es,%w0" : "=r" (es));
    return es;
}
inline void set_es(uint16_t es)
{
    asm volatile("movw %w0,%%es" : : "r" (es));
}

inline uint16_t get_fs()
{
    uint16_t fs;
    asm volatile("movw %%fs,%w0" : "=r" (fs));
    return fs;
}
inline void set_fs(uint16_t fs)
{
    asm volatile("movw %w0,%%fs" : : "r" (fs));
}

inline uint16_t get_gs()
{
    uint16_t gs;
    asm volatile("movw %%gs,%w0" : "=r" (gs));
    return gs;
}
inline void set_gs(uint16_t gs)
{
    asm volatile("movw %w0,%%gs" : : "r" (gs));
}

inline uint16_t get_ss()
{
    uint16_t ss;
    asm volatile("movw %%ss,%w0" : "=r" (ss));
    return ss;
}
inline void set_ss(uint16_t ss)
{
    asm volatile("movw %w0,%%ss" : : "r" (ss));
}

#define get_eax() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%eax, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_ebx() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%ebx, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_ecx() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%ecx, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_edx() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%edx, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_esi() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%esi, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_edi() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%edi, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_ebp() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%ebp, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_esp() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%esp, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_eflags() \
    ({ \
	register unsigned int _temp__; \
	asm volatile("pushfl; popl %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_eip() \
    ({ \
	register unsigned int _temp__; \
	asm("1: movl $1b, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	get_cr0() \
    ({ \
	register unsigned int _temp__; \
	asm volatile("mov %%cr0, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	set_cr0(value) \
    ({ \
	register unsigned int _temp__ = (value); \
	asm volatile("mov %0, %%cr0" : : "r" (_temp__)); \
     })

#ifdef HAVE_CR4
#define get_cr4() \
    ({ \
	register unsigned int _temp__; \
	asm volatile("mov %%cr4, %0" : "=r" (_temp__)); \
	_temp__; \
    })
#define set_cr4(value) \
    ({ \
	register unsigned int _temp__ = (value); \
	asm volatile("mov %0, %%cr4" : : "r" (_temp__)); \
     })
#else /* not HAVE_CR4 */
#define get_cr4() \
    ({ \
	register unsigned int _temp__; \
	asm volatile(".byte 0x0f,0x20,0xe0" : "=a" (_temp__)); \
	_temp__; \
    })
#define set_cr4(value) \
	asm volatile(".byte 0x0f,0x22,0xe0" : : "a" (value));
#endif /* HAVE_CR4 */

#define get_msw() \
    ({ \
	uint16_t _msw__; \
	asm volatile("smsw %0" : "=r" (_msw__)); \
	_msw__; \
    })

#define	get_cr2() \
    ({ \
	register unsigned int _temp__; \
	asm("mov %%cr2, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	get_cr3() \
    ({ \
	register unsigned int _temp__; \
	asm("mov %%cr3, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	set_cr3(value) \
    ({ \
	register unsigned int _temp__ = (value); \
	asm volatile("mov %0, %%cr3" : : "r" (_temp__)); \
     })

#define	set_ts() \
	set_cr0(get_cr0() | CR0_TS)

#define	clear_ts() \
	asm volatile("clts")

#define	get_tr() \
    ({ \
	uint16_t _seg__; \
	asm volatile("str %0" : "=rm" (_seg__) ); \
	_seg__; \
    })

#define	set_tr(seg) \
	asm volatile("ltr %0" : : "rm" ((uint16_t)(seg)) )

//extern void set_gdtr(unsigned int base, uint16_t limit);
#define set_gdtr(gdt_desc) \
    ({ \
	asm volatile("lgdt %0" : : "m" ((gdt_desc)->limit)); \
    })

//#define get_gdt() \
//    ({ \
//    unsigned int
//    })

#define set_idt(pseudo_desc) \
    ({ \
	asm volatile("lidt %0" : : "m" ((pseudo_desc)->limit)); \
    })

#define	get_ldt() \
    ({ \
	uint16_t _seg__; \
	asm volatile("sldt %0" : "=rm" (_seg__) ); \
	_seg__; \
    })

#define	set_ldt(seg) \
	asm volatile("lldt %0" : : "rm" ((uint16_t)(seg)) )

/*
 * Read the 64-bit timestamp counter (TSC) register.
 * Works only on Pentium and higher processors,
 * and in user mode only if the TSD bit in CR4 is not set.
 */
#if HAVE_RDTSC
#define get_tsc() \
    ({ \
	unsigned long low, high; \
	asm volatile("rdtsc" : "=d" (high), "=a" (low)); \
	((unsigned long long)high << 32) | low; \
    })
#define rdmsr(msr) \
    ({ \
	unsigned long low, high; \
	asm volatile("rdmsr" : "=d" (high), "=a" (low) : "c" (msr)); \
	((unsigned long long)high << 32) | low; \
    })
#define wrmsr(msr, high, low) \
    ({ \
	asm volatile("wrmsr" : : "d" (high), "a" (low), "c" (msr)); \
    })
#define wrmsrll(msr, val) \
    ({ \
	asm volatile("wrmsr" : : "A" (val), "c" (msr)); \
    })
#else
#define get_tsc() \
    ({ \
	unsigned long low, high; \
	asm volatile( \
	".byte 0x0f; .byte 0x31" \
	: "=d" (high), "=a" (low)); \
	((unsigned long long)high << 32) | low; \
    })
#define rdmsr(msr) \
    ({ \
	unsigned long low, high; \
	asm volatile(".byte 0x0f; .byte 0x32;" \
 	: "=d" (high), "=a" (low) : "c" (msr)); \
	((unsigned long long)high << 32) | low; \
    })
#define wrmsr(msr, high, low) \
    ({ \
	asm volatile(".byte 0x0f; .byte 0x30" \
	: : "d" (high), "a" (low), "c" (msr)); \
    })
#define wrmsrll(msr, val) \
    ({ \
	asm volatile(".byte 0x0f; .byte 0x30" \
	: : "A" (val), "c" (msr)); \
    })
#endif

/*
 * This doesn't set a processor register,
 * but it's often used immediately after setting one,
 * to flush the instruction queue.
 */
#define flush_instr_queue() \
	asm volatile( \
	"	jmp	0f\n" \
	"	0:" \
	)

#endif	/* _COSMOS_X86_PROC_REG_H_ */
