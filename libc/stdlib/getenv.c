#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/*
 * getenv --
 *	Returns ptr to value associated with name, if any, else NULL.
 */
char *
getenv(name)
	const char *name;
{
	extern char **environ;
	register int len;
	register const char *np;
	register char **p, *c;

	if (name == NULL || environ == NULL)
		return (NULL);
	for (np = name; *np && *np != '='; ++np)
		continue;
	len = np - name;
	for (p = environ; (c = *p) != NULL; ++p)
		if (strncmp(c, name, len) == 0 && c[len] == '=') {
			return (c + len + 1);
		}
	return (NULL);
}
