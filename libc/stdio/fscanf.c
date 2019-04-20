#include <stdio.h>
#include <stdarg.h>
#include "_doscan.h"

/* XXX kludge to work around absence of ungetc() */
typedef struct state
{
	FILE *fh;
	int ch;
} state;

static int
read_char(void *arg)
{
	state *st = (state*)arg;
	if (st->ch >= 0)
	{
		int c = st->ch;
		st->ch = -1;
		return c;
	}
	else
		return fgetc(st->fh);
}

static void
unread(int c, void *arg)
{
	state *st = (state*)arg;
	st->ch = c;
}

#if 0
static int
read_char(void *arg)
{
	return fgetc((FILE*)arg);
}

static void
unread(int c, void *arg)
{
	ungetc(c, (FILE*)arg);
}
#endif

int vfscanf(FILE *fh, const char *fmt, va_list args)
{
	return _doscan(fmt, args, read_char, unread, fh);
}

int
fscanf(FILE *fh, const char *fmt, ...)
{
	int nmatch = 0;
	va_list	args;
	state st;

	st.fh = fh;
	st.ch = -1;

	va_start(args, fmt);
	nmatch = vfscanf((FILE *)&st, fmt, args);	
	va_end(args);

	return nmatch;
}

