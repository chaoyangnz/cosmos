#include <stdio.h>
#include <sys/console.h>

/*
 * Note dependency on the kernel library.
 */
int getchar()
{
	return console_getchar();
}
