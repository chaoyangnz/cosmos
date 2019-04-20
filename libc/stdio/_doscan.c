#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "_doscan.h"

typedef int boolean_t;

/*
 * All I need is a miracle ...
 * to keep this from growing like all the other sscanf!
 */
int
_doscan(const unsigned char *fmt, va_list vp,
	int (*getc)(void *getc_arg),
	void (*ungetc)(int c, void *getc_arg),
	void *getc_arg)
{
	register	int c;
	boolean_t	neg;
	boolean_t	discard;
	int		vals = 0;

	while ((c = *fmt++) != 0) {

	    if (c != '%') {
	        if (isspace(c))
		{
			while (isspace(c = getc(getc_arg)));
			ungetc(c, getc_arg);
			continue;
		}
	    	else if (c == getc(getc_arg))
			continue;
		else
			break;	/* mismatch */
	    }

	    discard = 0;

	more_fmt:

	    c = *fmt++;

	    switch (c) {

	    case 'd':
	    {
		long n = 0;

		c = getc(getc_arg);

		neg =  c == '-';
		if (neg) c = getc(getc_arg);

		while (c >= '0' && c <= '9') {
		    n = n * 10 + (c - '0');
		    c = getc(getc_arg);
		}
		ungetc(c, getc_arg);

		if (neg) n = -n;

		/* done, store it away */
		if (!discard)
		{
			int *p = va_arg(vp, int *);
			*p = n;
		}

	        break;
	    }

	    case 'x':
	    {
		long n = 0;

		c = getc(getc_arg);

		neg =  c == '-';
		if (neg) c = getc(getc_arg);

		while (1)
		{
		    if ((c >= '0') && (c <= '9'))
			n = n * 16 + (c - '0');
		    else if ((c >= 'a') && (c <= 'f'))
			n = n * 16 + (c - 'a' + 10);
		    else if ((c >= 'A') && (c <= 'F'))
			n = n * 16 + (c - 'A' + 10);
		    else
			break;
		    c = getc(getc_arg);
		}
		ungetc(c, getc_arg);	/* retract lookahead */

		if (neg) n = -n;

		/* done, store it away */
		if (!discard)
		{
			int *p = va_arg(vp, int *);
			*p = n;
		}

	        break;
	    }

	    case 's':
	    {
		char *buf = NULL;

		if (!discard)
			buf = va_arg(vp, char *);

		c = getc(getc_arg);
		while (c && !isspace(c))
		{
		    if (!discard)
		    	*buf++ = c;
		    c = getc(getc_arg);
		}
		ungetc(c, getc_arg);	/* retract lookahead */

		if (!discard)
		    *buf = 0;

		break;
	    }

	    case '*':
	    	discard = 1;
		goto more_fmt;

	    default:
	        break;
	    }

	    if (!discard)
		vals++;
	}

	return vals;
}

