#include <kernel/segment.h>
#include <kernel/register.h>
#include <kernel/types.h>
#include <stddef.h>
#include <stdio.h>

segment_descriptor_t gdt[GDT_SIZE];
//static gdt_desc_t gdt_desc;

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

/* Set the base address in a segment descriptor.  */
static void
segment__fill_descriptor_base(segment_descriptor_t *desc, uint32_t base)
{
    desc->base_low = base & 0xffff;
    desc->base_med = (base >> 16) & 0xff;
    desc->base_high = base >> 24;
}

/* Set the size in a segment descriptor.  */
static void
segment__fill_descriptor_limit(segment_descriptor_t *desc, uint32_t limit)
{
    if (limit > 0xfffff)
    {
        limit >>= 12;
        desc->granularity |= SEG_SZ_GRANULARITY;
    }
    else
        desc->granularity &= ~SEG_SZ_GRANULARITY;
    desc->limit_low = limit & 0xffff;
    desc->limit_high = limit >> 16;
}

/* Fill a gate with particular values.  */
static void
segment__fill_gate(x86_gate_t *gate, uint32_t offset, uint16_t selector,
                   uint8_t access, uint8_t word_count)
{
    gate->offset_low = offset & 0xffff;
    gate->selector = selector;
    gate->word_count = word_count;
    gate->access = access | SEG_DESC_ACC_P;
    gate->offset_high = (offset >> 16) & 0xffff;
}

void
segment__setup()
{
    /* Initialize the 32-bit kernel code and data segment descriptors
       to point to the base of the kernel linear space region.  */
    segment__fill_segment_descriptor(&gdt[SEG_INDEX_KERNEL_CODE],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_K | SEG_DESC_ACC_CODE_R, SEG_SZ_32);
    segment__fill_segment_descriptor(&gdt[SEG_INDEX_KERNEL_DATA],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_K | SEG_DESC_ACC_DATA_W, SEG_SZ_32);

    /* Descriptors that direct-map all linear space.  */
    segment__fill_segment_descriptor(&gdt[SEG_INDEX_USER_CODE],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_U | SEG_DESC_ACC_CODE_R, SEG_SZ_32);
    segment__fill_segment_descriptor(&gdt[SEG_INDEX_USER_DATA],
                                     0x00000000, 0xffffffff,
                                     SEG_DESC_ACC_PL_U | SEG_DESC_ACC_DATA_W, SEG_SZ_32);

    segment__load_gdt();
}

void
segment__load_gdt() {
    gdt_desc_t gdt_desc = {
       .base = (addr_t)(&gdt),
       .limit = GDT_SIZE * 8 - 1
    };

    /* Load it into the CPU.  */
    set_gdtr(gdt_desc);
    /*
     * Reload all the segment registers from the new GDT.
     */
    set_cs(segment_selector(SEG_INDEX_KERNEL_CODE, 0, 0));
    set_ds(segment_selector(SEG_INDEX_KERNEL_DATA, 0, 0));
    set_es(segment_selector(SEG_INDEX_KERNEL_DATA, 0, 0));
    set_ss(segment_selector(SEG_INDEX_KERNEL_DATA, 0, 0));

    /*
     * Clear out the FS and GS registers by default,
     * since they're not needed for normal execution of GCC code.
     */
    set_fs(segment_selector(SEG_INDEX_NULL, 0, 0));
    set_gs(segment_selector(SEG_INDEX_NULL, 0, 0));
}

void segment__info() {
    gdt_desc_t gdt_des = get_gdtr();
    printf("GDT: %#x %#x CS: %#x DS: %#x ES: %#x SS: %#x FS: %#x GS: %#x \n", \
        gdt_des.base, gdt_des.limit, get_cs(), get_ds(), get_es(), get_ss(), get_fs(), get_gs());
}



