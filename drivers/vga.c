#include <trinity/vga.h>
#include <trinity/string.h>

static struct {
    uint8_t curr_row;
    uint8_t curr_col;
} vga_screen;

void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            VGA_MEMORY[(y * VGA_WIDTH) + x] = make_character(' ', make_color(BLACK, BLACK));
        }
    }
}

void screen_putchar(int x, int y, char c, uint8_t color) {
    VGA_MEMORY[y * VGA_WIDTH + x] = make_character(c, color);
}

void screen_writechar(char c, uint8_t color) {
    if (c == '\n') {
        vga_screen.curr_row += 1;
        vga_screen.curr_col = 0;
        return;
    }
    screen_putchar(vga_screen.curr_col, vga_screen.curr_row, c, color);
    vga_screen.curr_col += 1;
    if (vga_screen.curr_col >= VGA_WIDTH) {
        vga_screen.curr_row += 1;
        vga_screen.curr_col = 0;
    }
}
