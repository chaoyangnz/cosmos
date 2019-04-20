#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <fcntl.h>
#include <errno.h>

FILE *
fopen(const char *name, const char *mode)
{
//	int base_mode = O_RDONLY, flags = 0;
//	FILE *stream;
//
//	/* Find the appropriate Unix mode flags.  */
//	switch (*mode++)
//	{
//		case 'w':
//			base_mode = O_WRONLY;
//			flags |= O_CREAT | O_TRUNC;
//			break;
//		case 'a':
//			base_mode = O_WRONLY;
//			flags |= O_CREAT | O_APPEND;
//			break;
//	}
//	while (*mode)
//	{
//		if (*mode == '+')
//			base_mode = O_RDWR;
//		mode++;
//	}
//
//	if (!(stream = malloc(sizeof(*stream))))
//	{
//		errno = ENOMEM;
//		return 0;
//	}
//
//	if ((stream->_file = open(name, base_mode | flags)) < 0)
//	{
//		free(stream);
//		return 0;
//	}
//
//	stream->_flags &= ~(__SEOF|__SERR);
//	return stream;
}

