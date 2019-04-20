/*
 * This file defines stdin, stdout, and stderr in a manner similar
 * to the FreeBSD C library. 
 */

#include <unistd.h>
#include <stdio.h>

#define	std(flags, file) \
	{0,0,0,flags,file,{0},0, 0,     0,    0,   0,    0}
/*	 p r w flags file _bf z  cookie close read seek  write */

FILE __sF[3] = {
	std(0, STDIN_FILENO),	/* stdin */
	std(0, STDOUT_FILENO),	/* stdout */
	std(0, STDERR_FILENO)	/* stderr */
};
