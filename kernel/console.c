#include "kernel/console.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

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

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

static const uint32_t VGA_BASE = 0xB8000;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t console_row;
size_t console_column;
uint8_t console_color;
uint16_t* console_buffer;

void console_initialize(void)
{
    console_row = 0;
    console_column = 0;
    console_color = vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK);
    console_buffer = (uint16_t*) VGA_BASE;
    // clear
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            console_buffer[index] = vga_entry(' ', console_color);
        }
    }
}

void console_set_color(uint8_t color)
{
    console_color = color;
}

void console_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    console_buffer[index] = vga_entry(c, color);
}

int console_putchar(char c)
{
    if(c == '\n') {
        console_column = 0;
        console_row++;
        if(console_row == VGA_HEIGHT) {
            console_row = 0;
        }
    } else {
        console_put_entry_at(c, console_color, console_column, console_row);
        console_column++;
        if(console_column == VGA_WIDTH) {
            console_row++;
            if(console_row == VGA_HEIGHT) {
                console_row = 0;
            }
        }
    }
    return 0;
}

int console_putbytes(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        console_putchar(data[i]);
    return size;
}

int console_puts(const char *data)
{
    return console_putbytes(data, strlen(data));
}

int console_getchar() {
    return NULL;
}