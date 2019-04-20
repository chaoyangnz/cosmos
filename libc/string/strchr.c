#include <string.h>

char *strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == c)
			return (char*)s;
		if (*s == 0)
			return 0;
		s++;
	}
}

