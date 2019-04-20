#ifndef __DOSCAN_H_INCLUDED__
#define __DOSCAN_H_INCLUDED__

int _doscan(const unsigned char *fmt, va_list vp,
	int (*getc)(void *getc_arg),
	void (*ungetc)(int c, void *getc_arg),
	void *getc_arg);

#endif /* __DOSCAN_H_INCLUDED__ */
