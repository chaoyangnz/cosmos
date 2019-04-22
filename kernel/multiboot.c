#include <kernel/i386/multiboot.h>

multiboot_info_t*
get_multiboot_info() {
    multiboot_info_t* mbi;
	asm("movl %%ebx, %0"
	: "=r" (mbi));
	return mbi;
}