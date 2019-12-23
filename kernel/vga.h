#ifndef COSMOS_VGA_H
#define COSMOS_VGA_H

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
extern void vga__setup();
extern void vga__set_fg(enum vga_color fg);
extern void vga__set_bg(enum vga_color bg);
extern int	vga__putchar(char c);
extern int	vga__getchar();
extern int	vga__puts(const char *s);
extern int	vga__putbytes(const char *data, size_t size);

#endif //COSMOS_VGA_H
