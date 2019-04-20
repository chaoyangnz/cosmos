#include <stdio.h>

/* Simple puts() implementation that just uses putchar().
   Note that our printf() is implemented
   in terms of only puts() and putchar(), so that's all we need.
   The only reason the caller might want to replace this function
   is if putchar() has extremely high overhead for some reason.  */
int puts(const char *s)
{
	while (*s)
	{
		putchar(*s);
		s++;
	}
	putchar('\n');
	return 0;
}

