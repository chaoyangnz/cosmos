#include <stddef.h>
#include <string.h>

void *
memchr(s, c, n)
	const void *s;
	register unsigned char c;
	register size_t n;
{
	if (n != 0) {
		register const unsigned char *p = s;

		do {
			if (*p++ == c)
				return ((void *)(p - 1));
		} while (--n != 0);
	}
	return (NULL);
}
