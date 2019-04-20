#include <stdio.h>
#include <unistd.h>

int fwrite(void *buf, int size, int count, FILE *stream)
{
	int total;

	if ((total = size * count) == 0)
		return 0;

	total = write(fileno(stream), buf, total);

	if (total < 0)
		stream->_flags |= __SERR;

	return (total > 0 ? total/size : 0);
}

