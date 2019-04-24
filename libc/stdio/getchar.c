#include <stdio.h>
#include <kernel/vga.h>

/*
 * Note dependency on the kernel library.
 */
int getchar()
{
	return console_getchar();
}
