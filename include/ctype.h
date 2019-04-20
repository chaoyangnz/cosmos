#ifndef _C_CTYPE_H_
#define _C_CTYPE_H_

#include "compiler.h"

INLINE int isascii(int c);
INLINE int iscntrl(int c);
INLINE int isdigit(int c);
INLINE int isgraph(int c);
INLINE int islower(int c);
INLINE int isprint(int c);
INLINE int isspace(int c);
INLINE int isupper(int c);
INLINE int isxdigit(int c);
INLINE int isalpha(int c);
INLINE int isalnum(int c);
INLINE int ispunct(int c);
INLINE int toascii(int c);
INLINE int toupper(int c);
INLINE int tolower(int c);

INLINE int isascii(int c)
{
	return ((c & ~0x7f) == 0);
}

INLINE int iscntrl(int c)
{
	return ((c) < ' ') || ((c) > 126);
}

INLINE int isdigit(int c)
{
	return ((c) >= '0') && ((c) <= '9');
}

INLINE int isgraph(int c)
{
	return ((c) > ' ') && ((c) <= 126);
}

INLINE int islower(int c)
{
	return (c >= 'a') && (c <= 'z');
}

INLINE int isprint(int c)
{
	return ((c) >= ' ') && ((c) <= 126);
}

INLINE int isspace(int c)
{
	return ((c) == ' ') || ((c) == '\f')
		|| ((c) == '\n') || ((c) == '\r')
		|| ((c) == '\t') || ((c) == '\v');
}

INLINE int isupper(int c)
{
	return (c >= 'A') && (c <= 'Z');
}

INLINE int isxdigit(int c)
{
	return isdigit(c) ||
		((c >= 'A') && (c <= 'F')) ||
		((c >= 'a') && (c <= 'f'));
}

INLINE int isalpha(int c)
{
	return islower(c) || isupper(c);
}

INLINE int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

INLINE int ispunct(int c)
{
	return isgraph(c) && !isalnum(c);
}

INLINE int toascii(int c)
{
	return ((c) & 0x7f);
}

INLINE int toupper(int c)
{
	return ((c >= 'a') && (c <= 'z')) ? (c - 'a' + 'A') : c;
}

INLINE int tolower(int c)
{
	return ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 'a') : c;
}


#endif /* _C_CTYPE_H_ */
