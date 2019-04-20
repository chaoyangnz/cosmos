

#include <string.h>

char *
strcat(char *s, const char *add)
{
	register char *ret = s;

	while (*s) s++;

	while ((*s++ = *add++) != 0);

	return ret;
}
