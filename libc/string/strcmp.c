/*
 * File: 	limach/strcmp.c
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

#include <string.h>

int
strcmp(const char *s1, const char *s2)
{
register unsigned int a, b;



	while ( (a = *s1++), (b = *s2++), a && b) {
		if (a != b)
			return (a-b);
	}

	return a-b;
}
