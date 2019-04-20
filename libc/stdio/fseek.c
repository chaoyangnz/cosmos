#include <stdio.h>
#include <unistd.h>

int fseek(FILE *stream, long offset, int whence)
{
	f_offset_t off = lseek(fileno(stream), offset, whence);
	
	if (off < 0)
		stream->_flags |= __SERR;

	return (off < 0) ? -1 : 0;
}

