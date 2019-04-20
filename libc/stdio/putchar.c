#include <stdio.h>
#include <sys/console.h>

/*
 * Note dependency on the kernel library.
 */
int putchar(int c)
{
	return console_putchar(c);
}
