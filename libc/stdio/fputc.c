#include <stdio.h>
#include <unistd.h>

int fputc(int c, FILE *stream)
{
	char ch = c;

	int rc = write(fileno(stream), &ch, 1);

	if (rc < 0)
		stream->_flags |= __SERR;
	return rc;
}

