#include <stdio.h>
#include <kernel/console.h>

/*
 * Note dependency on the kernel library.
 */
int putchar(int c)
{
	return console_putchar(c);
}
