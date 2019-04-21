#ifndef _SYS_CONSOLE_H_
#define _SYS_CONSOLE_H_

#include <stddef.h>

/*
 * Exported console functions from the machine dependent code. These need
 * to be defined for simple console output to work.
 */
extern void console_initialize();
extern int	console_putchar(char c);
extern int	console_getchar();
extern int	console_puts(const char *s);
extern int	console_putbytes(const char *s, size_t len);

#endif /* _SYS_CONSOLE_H_ */
