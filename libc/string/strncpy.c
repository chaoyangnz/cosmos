
/*
 * File: 	libmach_sa/strncpy.c
 * Author:	Mary R. Thompson at Carnegie Mellon
 * Date:	Oct 13, 1992
 * Abstract:
 *	strncpy copies "count" characters from the "from" string to
 *	the "to" string. If "from" contains less than "count" characters
 *	"to" will be padded with null characters until exactly "count"
 *	characters have been written. The return value is a pointer
 *	to the "to" string.
 */

#include <stddef.h>
#include <string.h>

char *
strncpy(char *to, const char *from, size_t count)
{
    register char *ret = to;

    while (count > 0) {
	count--;
	if ((*to++ = *from++) == '\0')
	    break;
    }

    while (count > 0) {
	count--;
	*to++ = '\0';
    }

    return ret;
}
