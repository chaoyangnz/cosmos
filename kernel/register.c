#include <kernel/i386/register.h>



void cli() { asm("cli"); }
void sti() { asm("sti"); }
void cld() { asm("cld"); }
void clts() { asm("clts"); }

uint16_t get_cs()
{
    uint16_t cs;
    asm volatile("movw %%cs,%w0" : "=r" (cs));
    return cs;
}


uint16_t get_ds()
{
    uint16_t ds;
    asm volatile("movw %%ds,%w0" : "=r" (ds));
    return ds;
}

void set_ds(uint16_t ds)
{
    asm volatile("movw %w0,%%ds" : : "r" (ds));
}

uint16_t get_es()
{
    uint16_t es;
    asm volatile("movw %%es,%w0" : "=r" (es));
    return es;
}

void set_es(uint16_t es)
{
    asm volatile("movw %w0,%%es" : : "r" (es));
}

uint16_t get_fs()
{
    uint16_t fs;
    asm volatile("movw %%fs,%w0" : "=r" (fs));
    return fs;
}
void set_fs(uint16_t fs)
{
    asm volatile("movw %w0,%%fs" : : "r" (fs));
}

uint16_t get_gs()
{
    uint16_t gs;
    asm volatile("movw %%gs,%w0" : "=r" (gs));
    return gs;
}
void set_gs(uint16_t gs)
{
    asm volatile("movw %w0,%%gs" : : "r" (gs));
}

uint16_t get_ss()
{
    uint16_t ss;
    asm volatile("movw %%ss,%w0" : "=r" (ss));
    return ss;
}
void set_ss(uint16_t ss)
{
    asm volatile("movw %w0,%%ss" : : "r" (ss));
}

uint32_t get_eflags()
{
    register uint32_t _temp__;
    asm volatile("pushfl; popl %0" : "=r" (_temp__));
    return _temp__;
}

void set_eflags(uint32_t eflags)
{
    asm volatile(
    "	pushl %0\n"
    "	popfl" : : "r" (eflags));
}


uint32_t get_eax()
{
    register uint32_t _temp__;
    asm("movl %%eax, %0" : "=r" (_temp__));
    return _temp__;
}

uint32_t get_ebx()
{
	register uint32_t _temp__;
	asm("movl %%ebx, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_ecx()
{
	register uint32_t _temp__;
	asm("movl %%ecx, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_edx()
{
	register uint32_t _temp__;
	asm("movl %%edx, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_esi()
{
	register uint32_t _temp__;
	asm("movl %%esi, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_edi()
{
	register uint32_t _temp__;
	asm("movl %%edi, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_ebp()
{
	register uint32_t _temp__;
	asm("movl %%ebp, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_esp()
{
	register uint32_t _temp__;
	asm("movl %%esp, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_eip()
{
	register uint32_t _temp__;
	asm("1: movl $1b, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_cr0()
{
	register uint32_t _temp__;
	asm volatile("mov %%cr0, %0" : "=r" (_temp__));
	return _temp__;
}

void set_cr0(uint32_t value)
{
	register uint32_t _temp__ = (value);
	asm volatile("mov %0, %%cr0" : : "r" (_temp__));
 }

uint32_t get_cr4()
{
	register uint32_t _temp__;
	asm volatile("mov %%cr4, %0" : "=r" (_temp__));
	return _temp__;
}
void set_cr4(uint32_t value)
{
	register uint32_t _temp__ = (value);
	asm volatile("mov %0, %%cr4" : : "r" (_temp__));
 }


uint32_t get_msw()
{
	uint16_t _msw__;
	asm volatile("smsw %0" : "=r" (_msw__));
    return _msw__;
}

uint32_t get_cr2()
{
	register uint32_t _temp__;
	asm("mov %%cr2, %0" : "=r" (_temp__));
	return _temp__;
}

uint32_t get_cr3()
{
	register uint32_t _temp__;
	asm("mov %%cr3, %0" : "=r" (_temp__));
	return _temp__;
}

void set_cr3(uint32_t value)
{
	register uint32_t _temp__ = (value);
	asm volatile("mov %0, %%cr3" : : "r" (_temp__));
 }

void set_ts()
{
    set_cr0(get_cr0() | CR0_TS);
}

void clear_ts()
{
    asm volatile("clts");
}

uint16_t get_tr()
{
	uint16_t _seg__;
	asm volatile("str %0" : "=rm" (_seg__) );
    return _seg__;
}

void set_tr(uint16_t seg)
{
    asm volatile("ltr %0" : : "rm" ((uint16_t)(seg)) );
}

void set_gdtr(descriptor_table_desc_t gdt_desc)
{
	asm volatile("lgdt %0" : : "m" (gdt_desc));
}

//uint16_t get_gdtr()
//{
//    uint16_t _seg__;
//    asm volatile("sgdt %0" : "=rm" (_seg__) );
//    return _seg__;
//}

void set_idt(descriptor_table_desc_t pseudo_desc)
{
	asm volatile("lidt %0" : : "m" (pseudo_desc));
}

uint16_t get_ldt()
{
	uint16_t _seg__;
	asm volatile("sldt %0" : "=rm" (_seg__) );
    return _seg__;
}

void set_ldt(uint16_t seg)
{
    asm volatile("lldt %0" : : "rm" ((uint16_t)(seg)) );
}

uint32_t get_tsc()
{
	unsigned long low, high;
	asm volatile(
	".byte 0x0f; .byte 0x31"
	: "=d" (high), "=a" (low));
    return ((unsigned long long)high << 32) | low;
}

uint32_t rdmsr(uint32_t msr)
{
	unsigned long low, high;
	asm volatile(".byte 0x0f; .byte 0x32;"
 	: "=d" (high), "=a" (low) : "c" (msr));
	((uint64_t)high << 32) | low;
}

void wrmsr(uint32_t msr, uint32_t high, uint32_t low)
{
	asm volatile(".byte 0x0f; .byte 0x30"
	: : "d" (high), "a" (low), "c" (msr));
}

void wrmsrll(uint32_t msr, uint32_t val)
{
	asm volatile(".byte 0x0f; .byte 0x30"
	: : "A" (val), "c" (msr));
}
