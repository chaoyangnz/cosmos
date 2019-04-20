/*
 * File: 	limach/memcmp.c
 * Author:	Robert V. Baron at Carnegie Mellon
 * Date:	Oct 13, 1992
 * Abstract:
 *	strcmp (s1, s2) compares the strings "s1" and "s2".
 *	It returns 0 if the strings are identical. It returns
 *	> 0 if the first character that differs into two strings
 *	is larger in s1 than in s2 or if s1 is longer than s2 and 
 *	the contents  are identical up to the length of s2.
 *	It returns < 0 if the first differing character is smaller 
 *	in s1 than in s2 or if s1 is shorter than s2 and the
 *	contents are identical upto the length of s1.
 */

#include <stddef.h>
#include <string.h>
#undef memcmp

int
memcmp(const void *s1v, const void *s2v, size_t size)
{
	register const char *s1 = s1v, *s2 = s2v;
	register unsigned int a, b;

	while (size-- > 0) {
		if ((a = *s1++) != (b = *s2++))
			return (a-b);
	}

	return 0;
}
