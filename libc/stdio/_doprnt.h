#ifndef __DOPRNT_H_INCLUDED__
#define __DOPRNT_H_INCLUDED__

void _doprnt(
	const char	*fmt,
	va_list		args,
	int		radix,		/* default radix - for '%r' */
 	void		(*putc)(),	/* character output */
	char		*putc_arg);	/* argument for putc */

/* #define DOPRNT_FLOATS 1 */

#endif /* __DOPRNT_H_INCLUDED__ */
