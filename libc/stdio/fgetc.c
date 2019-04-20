#include <stdio.h>
#include <unistd.h>

int fgetc(FILE *stream)
{
	unsigned char c;
	int rc = read(fileno(stream), &c, 1);

	switch (rc) {
	case 1:
		return c;

	case 0:
		stream->_flags |= __SEOF;
		break;

	default:
		stream->_flags |= __SERR;
	}
	return -1;
}

