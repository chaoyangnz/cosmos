#include <kernel/i386/segment.h>
#include <kernel/i386/register.h>
#include <kernel/i386/types.h>
#include <stddef.h>
#include <stdio.h>

struct segment_descriptor gdt[GDT_SIZE];

void gdt_init()
{
    /* Initialize the 32-bit kernel code and data segment descriptors
       to point to the base of the kernel linear space region.  */
    fill_segment_descriptor(&gdt[KERNEL_CODE / 8],
                            0x00000000, 0xffffffff,
                            ACC_PL_K | ACC_CODE_R, SZ_32);
    fill_segment_descriptor(&gdt[KERNEL_DATA / 8],
                            0x00000000, 0xffffffff,
                            ACC_PL_K | ACC_DATA_W, SZ_32);

    /* Descriptors that direct-map all linear space.  */
    fill_segment_descriptor(&gdt[USER_CODE / 8],
                            0x00000000, 0xffffffff,
                            ACC_PL_U | ACC_CODE_R, SZ_32);
    fill_segment_descriptor(&gdt[USER_DATA / 8],
                            0x00000000, 0xffffffff,
                            ACC_PL_U | ACC_DATA_W, SZ_32);
}

static struct gdt_descriptor gdt_desc;

void gdt_load() {
    gdt_desc.base = (addr_t)(&gdt);
    gdt_desc.limit = GDT_SIZE * 8 - 1;

    /* Load it into the CPU.  */
    set_gdt(&gdt_desc);
    /*
     * Reload all the segment registers from the new GDT.
     */
    set_cs(KERNEL_CODE);
    set_ds(KERNEL_DATA);
    set_es(KERNEL_DATA);
    set_ss(KERNEL_DATA);

    /*
     * Clear out the FS and GS registers by default,
     * since they're not needed for normal execution of GCC code.
     */
    set_fs(0);
    set_gs(0);
}



