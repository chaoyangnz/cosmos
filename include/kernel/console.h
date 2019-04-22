#ifndef _SYS_CONSOLE_H_
#define _SYS_CONSOLE_H_

#include <stddef.h>

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

/*
 * Exported console functions from the machine dependent code. These need
 * to be defined for simple console output to work.
 */
extern void console_initialize();
extern void console_set_color(uint8_t color);
extern int	console_putchar(char c);
extern int	console_getchar();
extern int	console_puts(const char *s);
extern int	console_putbytes(const char *s, size_t len);

#endif /* _SYS_CONSOLE_H_ */
