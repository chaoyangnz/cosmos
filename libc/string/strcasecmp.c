#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <sys/i386/types.h>

int
strcasecmp(s1, s2)
	const char *s1, *s2;
{
	register const uchar_t
			*us1 = (const uchar_t *)s1,
			*us2 = (const uchar_t *)s2;

	while (tolower(*us1) == tolower(*us2++))
		if (*us1++ == '\0')
			return (0);
	return (tolower(*us1) - tolower(*--us2));
}

int
strncasecmp(s1, s2, n)
	const char *s1, *s2;
	register size_t n;
{
	if (n != 0) {
		register const uchar_t
				*us1 = (const uchar_t *)s1,
				*us2 = (const uchar_t *)s2;

		do {
			if (tolower(*us1) != tolower(*us2++))
				return (tolower(*us1) - tolower(*--us2));
			if (*us1++ == '\0')
				break;
		} while (--n != 0);
	}
	return (0);
}
