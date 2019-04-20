#include <stdio.h>
#include <unistd.h>

long ftell(FILE *stream)
{
	return lseek(fileno(stream), 0, SEEK_CUR);
}

