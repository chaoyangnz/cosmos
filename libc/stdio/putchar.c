#include <stdio.h>
#include "../../kernel/vga.h"

/*
 * Note dependency on the kernel library.
 */
int putchar(int c)
{
	return vga__putchar(c);
}
