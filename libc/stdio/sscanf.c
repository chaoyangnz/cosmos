#include <stdarg.h>
#include "_doscan.h"

static int
readchar(arg)
	void *arg;
{
	return *(*(unsigned char**)arg)++;
}

static void
unchar(c, arg)
	int c;
	void *arg;
{
	(*(unsigned char**)arg)--;
}

int 
vsscanf(s, fmt, args)
	char *s;
	char *fmt;
	va_list args;
{
	return _doscan(fmt, args, readchar, unchar, &s);
}

int 
sscanf(char *s, char *fmt, ...)
{
	int nmatch = 0;
        va_list	args;

	va_start(args, fmt);
	nmatch = vsscanf(s, fmt, args);
	va_end(args);

	return nmatch; 
}

