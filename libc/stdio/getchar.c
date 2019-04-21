#include <stdio.h>
#include <kernel/console.h>

/*
 * Note dependency on the kernel library.
 */
int getchar()
{
	return console_getchar();
}
