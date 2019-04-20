#include <string.h>
#include <stdlib.h>

char *strstr(const char *haystack, const char *needle)
{
	int hlen = strlen(haystack);
	int nlen = strlen(needle);

	while (hlen >= nlen)
	{
		if (!memcmp(haystack, needle, nlen))
			return (char *)haystack;

		haystack++;
		hlen--;
	}
	return 0;
}

