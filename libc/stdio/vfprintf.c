#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "_doprnt.h"

#define	PRINTF_BUFMAX	128

struct printf_state {
	FILE *stream;
	char buf[PRINTF_BUFMAX];
	unsigned int index;
};


static void
flush(struct printf_state *state)
{
	if (state->index > 0)
	{
		write(fileno(state->stream), state->buf, state->index);
		state->index = 0;
	}
}

static void
dochar(void *arg, int c)
{
	struct printf_state *state = (struct printf_state *) arg;

	if (state->index >= PRINTF_BUFMAX)
		flush(state);

	state->buf[state->index] = c;
	state->index++;
}

/*
 * Printing (to console)
 */
int vfprintf(FILE *stream, const char *fmt, va_list args)
{
	struct printf_state state;

	state.stream = stream;
	state.index = 0;
	_doprnt(fmt, args, 0, (void (*)())dochar, (char *) &state);

	flush(&state);

	return 0;
}

