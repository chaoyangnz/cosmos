#include <stdarg.h>
#include "_doprnt.h"

#define SPRINTF_UNLIMITED -1
struct sprintf_state {
      char *buf;
      unsigned int len;
      unsigned int max;
};

static void
savechar(char *arg, int c)
{
	struct sprintf_state *state = (struct sprintf_state *)arg;
	
	if (state->max != SPRINTF_UNLIMITED)
	{
		if (state->len == state->max)
			return;
	}

	state->len++;
	*state->buf = c;
	state->buf++;
}

int vsprintf(char *s, const char *fmt, va_list args)
{
	struct sprintf_state state;
	state.max = SPRINTF_UNLIMITED;
	state.len = 0;
	state.buf = s;

	_doprnt(fmt, args, 0, (void (*)()) savechar, (char *) &state);
	*(state.buf) = '\0';

	return state.len;
}

int vsnprintf(char *s, int size, const char *fmt, va_list args)
{
	struct sprintf_state state;
	state.max = size;
	state.len = 0;
	state.buf = s;

	_doprnt(fmt, args, 0, (void (*)()) savechar, (char *) &state);
	*(state.buf) = '\0';

	return state.len;
}

int sprintf(char *s, const char *fmt, ...)
{
	va_list	args;
	int err;

	va_start(args, fmt);
	err = vsprintf(s, fmt, args);
	va_end(args);

	return err;
}

int snprintf(char *s, int size, const char *fmt, ...)
{
	va_list	args;
	int err;

	va_start(args, fmt);
	err = vsnprintf(s, size, fmt, args);
	va_end(args);

	return err;
}

