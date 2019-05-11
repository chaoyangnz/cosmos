#include "eden.h"

#include "segment.h"
#include "register.h"
#include <stdint.h>
#include "memory.h"

static gdt_t *gdt_ptr BOOT_BSS_SECTION;

static void segment__fill_segment_descriptor(segment_descriptor_t *desc, uint32_t base, uint32_t limit, uint8_t access,
        uint8_t sizebits) BOOT_SECTION;

/* Load the base GDT into the CPU.  */
static void segment__load_gdt() BOOT_SECTION;

void
segment__setup()
{
    gdt_ptr = (gdt_t *)va_to_pa(&gdt);
    /* Initialize the 32-bit kernel code and data segment descriptors
       to point to the base of the kernel linear space region.  */
    segment__fill_segment_descriptor(&(*gdt_ptr)[SEG_INDEX_KERNEL_CODE],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_K | SEG_DESC_ACC_CODE_R, SEG_SZ_32);
    segment__fill_segment_descriptor(&(*gdt_ptr)[SEG_INDEX_KERNEL_DATA],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_K | SEG_DESC_ACC_DATA_W, SEG_SZ_32);

    /* Descriptors that direct-map all linear space.  */
    segment__fill_segment_descriptor(&(*gdt_ptr)[SEG_INDEX_USER_CODE],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_U | SEG_DESC_ACC_CODE_R, SEG_SZ_32);
    segment__fill_segment_descriptor(&(*gdt_ptr)[SEG_INDEX_USER_DATA],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_U | SEG_DESC_ACC_DATA_W, SEG_SZ_32);

    segment__load_gdt();
}

/* Fill a segment descriptor.  */
static void
segment__fill_segment_descriptor(segment_descriptor_t *desc, uint32_t base, uint32_t limit, uint8_t access,
                                 uint8_t sizebits)
{
    if (limit > 0xfffff)
    {
        limit >>= 12;
        sizebits |= SEG_SZ_GRANULARITY;
    }
    desc->limit_low = limit & 0xffff;
    desc->base_low = base & 0xffff;
    desc->base_med = (base >> 16) & 0xff;
    desc->access = access | SEG_DESC_ACC_P;
    desc->limit_high = limit >> 16;
    desc->granularity = sizebits;
    desc->base_high = base >> 24;
}

static void
segment__load_gdt() {
    gdt_desc_t gdt_desc = {
       .base = (addr_t)(gdt_ptr),
       .limit = GDT_SIZE * 8 - 1
    };
    /* Load it into the CPU.  */
    asm volatile("lgdt %0" : : "m" (gdt_desc));

    set_cs(segment_selector(SEG_INDEX_KERNEL_CODE, 0, 0));

    asm volatile (
    "movw %w0, %%ds \n"
    : : "r" (segment_selector(SEG_INDEX_KERNEL_DATA, 0, 0))
    );

    asm volatile (
    "movw %w0, %%es \n"
    : : "r" (segment_selector(SEG_INDEX_KERNEL_DATA, 0, 0))
    );

    asm volatile (
    "movw %w0, %%ss \n"
    : : "r" (segment_selector(SEG_INDEX_KERNEL_DATA, 0, 0))
    );

    asm volatile (
    "movw %w0, %%fs \n"
    : : "r" (segment_selector(SEG_INDEX_NULL, 0, 0))
    );

    asm volatile (
    "movw %w0, %%gs \n"
    : : "r" (segment_selector(SEG_INDEX_NULL, 0, 0))
    );
}

void segment__after_boot() {
    // fix gdtr to virtual address
    gdt_desc_t gdt_desc = {
            .base = (addr_t)(&gdt),
            .limit = GDT_SIZE * 8 - 1
    };
    asm volatile("lgdt %0" : : "m" (gdt_desc));
}



