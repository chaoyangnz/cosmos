#include <string.h>

char *
strrchr(const char *s, int c)
{
	char *save;

	for (save = NULL; *s != NULL; s++)
		if (*s == c)
			save = (char *)s;

	return save;
}
