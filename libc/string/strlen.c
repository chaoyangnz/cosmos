
/*
 * File: 	limach/strlen.c
 * Author:	Robert V. Baron at Carnegie Mellon
 * Date:	Oct 13, 1992
 * Abstract:
 *	strlen returns the number of characters in "string" preceeding 
 *	the terminating null character.
 */

#include <string.h>

size_t
strlen(const char *string)
{
    const char *ret = string;

    while (*string++);

    return string - 1 - ret;

}
