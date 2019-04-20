#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream)
{
	close(fileno(stream));
	if ((stream != stdin) &&
	    (stream != stdout) &&
	    (stream != stderr))
		free(stream);

	return 0;
}

