#include <stdio.h>
#include <stdarg.h>

int
fprintf(FILE *stream, const char *fmt, ...)
{
	va_list	args;
	int ret;

	va_start(args, fmt);
	ret = vfprintf(stream, fmt, args);
	va_end(args);

	return ret;
}

