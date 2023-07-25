#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stddef.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *) 0xB8000;

enum VGAColor {
    BLACK           = 0,
    BLUE            = 1,
    GREEN           = 2,
    CYAN            = 3,
    RED             = 4,
    MAGENTA         = 5,
    BROWN           = 6,
    LIGHTGRAY       = 7,
    DARKGRAY        = 8,
    LIGHTBLUE       = 9,
    LIGHTGREEN      = 10,
    LIGHTCYAN       = 11,
    LIGHTRED        = 12,
    LIGHTMAGENTA    = 13,
    YELLOW          = 14,
    WHITE           = 15
};

static uint8_t make_color(enum VGAColor background_color, enum VGAColor foreground_color) {
    return (background_color << 4) + foreground_color;
}

static uint16_t make_character(char c, uint8_t color) {
    return (color << 8) | c;
}

void clear_screen(void);
void screen_putchar(int x, int y, char c, uint8_t color);
void screen_writechar(char c, uint8_t color);

#endif