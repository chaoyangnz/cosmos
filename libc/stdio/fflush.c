#include <stdio.h>
#include <errno.h>
//#include <fd.h>

/*
 * fflush
 *
 * Since the oskit stdio doesn't buffer at all, we just return 
 * success.  We do try and check for bogus stream pointers though.
 */
int
fflush(FILE *stream) 
{
	/* NULL isn't really an error, since it means that we're 
	 * supposed to flush all streams.  So just return success.
	 */
	if (stream == NULL)
		return 0;

//	if (fd_check_stream(fileno(stream)))
//		return EOF;

	return 0;
}
