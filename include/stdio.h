#ifndef _C_STDIO_H
#define _C_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#include "kernel/types.h"
#include "compiler.h"

/* This is a very naive standard I/O implementation
   which simply chains to the low-level I/O routines
   without doing any buffering or anything.  */

#ifndef NULL
#define NULL 0
#endif

/*
 * This stuff comes from the FreeBSD C library header file. It is
 * duplicated here so that the min C library is binary compatible
 * with the FreeBSD C library
 */
#undef  __P
#define __P(protos)	protos

typedef f_offset_t	fpos_t;

/* stdio buffers */
struct __sbuf {
	unsigned char *_base;
	int	_size;
};

typedef	struct __sFILE {
	unsigned char *_p;	/* current position in (some) buffer */
	int	_r;		/* read space left for getc() */
	int	_w;		/* write space left for putc() */
	short	_flags;		/* flags, below; this FILE is free if 0 */
	short	_file;		/* fileno, if Unix descriptor, else -1 */
	struct	__sbuf _bf;	/* the buffer (at least 1 byte, if !NULL) */
	int	_lbfsize;	/* 0 or -_bf._size, for inline putc */

	/* operations */
	void	*_cookie;	/* cookie passed to io functions */
	int	(*_close) __P((void *));
	int	(*_read)  __P((void *, char *, int));
	fpos_t	(*_seek)  __P((void *, fpos_t, int));
	int	(*_write) __P((void *, const char *, int));

	/* separate buffer for long sequences of ungetc() */
	struct	__sbuf _ub;	/* ungetc buffer */
	unsigned char *_up;	/* saved _p when _p is doing ungetc data */
	int	_ur;		/* saved _r when _r is counting ungetc data */

	/* tricks to meet minimum requirements even when malloc() fails */
	unsigned char _ubuf[3];	/* guarantee an ungetc() buffer */
	unsigned char _nbuf[1];	/* guarantee a getc() buffer */

	/* separate buffer for fgetln() when line crosses buffer boundary */
	struct	__sbuf _lb;	/* buffer for fgetln() */

	/* Unix stdio files get aligned to block boundaries on fseek() */
	int	_blksize;	/* stat.st_blksize (may be != _bf._size) */
	fpos_t	_offset;	/* current lseek gdt_address (see WARNING) */
} FILE;

extern FILE __sF[];

#define	__SEOF		0x0020		/* found EOF */
#define	__SERR		0x0040		/* found error */

#define	stdin		(&__sF[0])
#define	stdout		(&__sF[1])
#define	stderr		(&__sF[2])

#define	feof(p)		(((p)->_flags & __SEOF) != 0)
#define	ferror(p)	(((p)->_flags & __SERR) != 0)
#define	clearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	fileno(p)	((p)->_file)

/*
 * End of FreeBSD duplicated stuff.
 */

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#ifndef EOF
#define EOF -1
#endif

#ifndef BUFSIZ
#define BUFSIZ	1024
#endif



extern int putchar(int __c);
extern int puts(const char *str);

extern int printf(const char *format, ...);
extern int vprintf(const char* format, va_list va);
extern int sprintf(char* buffer, const char* format, ...);
extern int snprintf(char* buffer, size_t count, const char* format, ...);
extern int vsprintf(char *buffer, const char *format, va_list va);
extern int vsnprintf(char* buffer, size_t count, const char* format, va_list va);
//  printf with output function
extern int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);

extern int getchar(void);
extern char *gets(char *str);

extern char *fgets(char *str, int __size, FILE *stream);
extern FILE *fopen(const char *path, const char *mode);
extern FILE *fdopen(int fd, const char *mode);
extern int fflush(FILE *stream);
extern int fclose(FILE *stream);
extern int fread(void *buf, int __size, int __count, FILE *stream);
extern int fwrite(void *buf, int __size, int __count, FILE *stream);
extern int fputc(int __c, FILE *stream);
extern int fputs(const char *str, FILE *stream);
extern int fgetc(FILE *stream);
extern int fprintf(FILE *stream, const char *format, ...);
extern int vfprintf(FILE *stream, const char *format, va_list __vl);
extern int fscanf(FILE *stream, const char *format, ...);
extern int sscanf(const char *str, const char *format, ...);
extern int fseek(FILE *stream, long __offset, int __whence);
extern long ftell(FILE *stream);
extern void rewind(FILE *stream);
extern int rename(const char *from, const char *to);
extern int remove(const char *path);

void dohexdump(void *base, void *buf, int __len, int __bytes);
#define hexdumpb(base, buf, nbytes) dohexdump(base, buf, nbytes, 0)
#define hexdumpw(base, buf, nwords) dohexdump(base, buf, nwords, 1)
void perror(const char *string);

#define putc(c, stream) fputc(c, stream)


#endif /* _C_STDIO_H */
