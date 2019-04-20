
/*
 * File: 	libmach_sa/strcpy.c
 * Author:	Robert V. Baron  at Carnegie Mellon
 * Date:	Oct 13, 1992
 * Abstract:
 *	strcpy copies the contents of the string "from" including 
 *	the null terminator to the string "to". A pointer to "to"
 *	is returned.
 */

#include <string.h>

char *
strcpy(char *to, const char *from)
{
register char *ret = to;

	while ((*to++ = *from++) != 0);

	return ret;
}
