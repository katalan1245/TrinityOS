#include <trinity/print.h>
#include <trinity/string.h>

void kprint(const char *str) {
    size_t len = strlen(str);
    uint8_t white = make_color(BLACK, WHITE);
    for (int i = 0; i < len; ++i) {
        screen_writechar(str[i], white);
    }
}

void kprint_num(int num, int base) {
    char str[NUM_STR_SIZE];
    itoa(num, str, base);
    kprint(str);
}