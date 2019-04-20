#include <string.h>

void *
memset(void *tov, int c, unsigned int len)
{
	register char *to = tov;

	while (len-- > 0)
		*to++ = c;

	return tov;
}

