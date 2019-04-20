#include <stdio.h>
#include <unistd.h>
#include <string.h>

int
fputs(const char *str, FILE *stream)
{
        int rc = write(fileno(stream), str, strlen(str));

	if (rc < 0) {
		stream->_flags |= __SERR;
		return EOF;
	}

	return rc;
}

