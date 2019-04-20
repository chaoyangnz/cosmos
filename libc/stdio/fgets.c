#include <stdio.h>
#include <unistd.h>

char *
fgets(char *str, int size, FILE *stream)
{
	int i;
	int c;

	if (size <= 0)
		return NULL;

	/*
	 * Special case for stdin to call read for the whole size,
	 * since console read will stop at the newline and do line
	 * discipline stuff for us.
	 */
	if (stream == stdin) {
		int rc = read(fileno(stream), str, size);
		if (rc > 0)
			return str;
		if (rc < 0)
			stream->_flags |= __SERR;
		else
			stream->_flags |= __SEOF;
		return NULL;
	}

	i = 0;
	while (i < size) {
		c = fgetc(stream);
		if (c == EOF) {
			if (i == 0)
				return NULL;
			break;
		}
		str[i++] = c;
		if (c == '\n')
			break;
	}
	if (i < size)
		str[i] = '\0';
	return str;
}
