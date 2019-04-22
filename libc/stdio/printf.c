#include <stdio.h>
#include <stdarg.h>
#include <kernel/console.h>
#include "_doprnt.h"

/* This version of printf is implemented in terms of putchar and puts.  */

#define	PRINTF_BUFMAX	128

struct printf_state {
	char buf[PRINTF_BUFMAX];
	unsigned int index;
};

static void
flush(struct printf_state *state)
{
	/*
	 * It would be nice to call write(1,) here, but if fd_set_console
	 * has not been called, it will break.
	 */
	console_putbytes((const char *) state->buf, state->index);

	state->index = 0;
}

static void
printf_char(arg, c)
	char *arg;
	int c;
{
	struct printf_state *state = (struct printf_state *) arg;

	if (c == '\n')
	{
		state->buf[state->index] = 0;
		puts(state->buf);
		state->index = 0;
	}
	else if ((c == 0) || (state->index >= PRINTF_BUFMAX))
	{
		flush(state);
		putchar(c);
	}
	else
	{
		state->buf[state->index] = c;
		state->index++;
	}
}

/*
 * Printing (to console)
 */
int vprintf(const char *fmt, va_list args)
{
	struct printf_state state = {
        .buf = {0},
        .index = 0
	};
	_doprnt(fmt, args, 0, (void (*)())printf_char, (char *) &state);

	if (state.index != 0)
	    flush(&state);

	/* _doprnt currently doesn't pass back error codes,
	   so just assume nothing bad happened.  */
	return 0;
}

int
printf(const char *fmt, ...)
{
	va_list	args;
	int err;

	va_start(args, fmt);
	err = vprintf(fmt, args);
	va_end(args);

	return err;
}
