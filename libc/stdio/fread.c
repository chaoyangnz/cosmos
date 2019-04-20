#include <stdio.h>
#include <unistd.h>

int fread(void *buf, int size, int count, FILE *stream)
{
	int total;

	if ((total = size * count) == 0)
		return 0;

	total = read(fileno(stream), buf, total);

	if (total == 0)
		stream->_flags |= __SEOF;

	if (total < 0)
		stream->_flags |= __SERR;

	return (total > 0 ? total/size : 0);
}

