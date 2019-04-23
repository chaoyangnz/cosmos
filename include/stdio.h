#ifndef _C_STDIO_H
#define _C_STDIO_H

#include "kernel/i386/types.h"
#include "compiler.h"
#include "stdarg.h"

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
extern int puts(const char *__str);
extern int printf(const char *__format, ...);
extern int vprintf(const char *__format, va_list __vl);
extern int sprintf(char *__dest, const char *__format, ...);
extern int snprintf(char *__dest, int __size, const char *__format, ...);
extern int vsprintf(char *__dest, const char *__format, va_list __vl);
extern int vsnprintf(char *__dest, int __size, const char *__format, va_list __vl);
extern int getchar(void);
extern char *gets(char *__str);
extern char *fgets(char *__str, int __size, FILE *__stream);
extern FILE *fopen(const char *__path, const char *__mode);
extern FILE *fdopen(int fd, const char *__mode);
extern int fflush(FILE *stream);
extern int fclose(FILE *__stream);
extern int fread(void *__buf, int __size, int __count, FILE *__stream);
extern int fwrite(void *__buf, int __size, int __count, FILE *__stream);
extern int fputc(int __c, FILE *__stream);
extern int fputs(const char *str, FILE *stream);
extern int fgetc(FILE *__stream);
extern int fprintf(FILE *__stream, const char *__format, ...);
extern int vfprintf(FILE *__stream, const char *__format, va_list __vl);
extern int fscanf(FILE *__stream, const char *__format, ...);
extern int sscanf(const char *__str, const char *__format, ...);
extern int fseek(FILE *__stream, long __offset, int __whence);
extern long ftell(FILE *__stream);
extern void rewind(FILE *__stream);
extern int rename(const char *__from, const char *__to);
extern int remove(const char *__path);
void dohexdump(void *__base, void *__buf, int __len, int __bytes);
#define hexdumpb(base, buf, nbytes) dohexdump(base, buf, nbytes, 0)
#define hexdumpw(base, buf, nwords) dohexdump(base, buf, nwords, 1)
void perror(const char *__string);

#define putc(c, stream) fputc(c, stream)


#endif /* _C_STDIO_H */
