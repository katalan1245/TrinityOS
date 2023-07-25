#include <trinity/string.h>



void *memmove(void *destination, const void* source, size_t num) {
    char *p_dest = (char *) destination;
    const char *p_src = (const char *) source;
    char tmp[num];
    for (int i = 0; i < num; ++i) {
        *(tmp + i) = *(p_src + i);
    }

    for (int i = 0; i < num; ++i) {
        *(p_dest + i) = *(tmp + i);
    }
    return destination;
}

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) { len++; }
    return len;
}

char *itoa(int value, char *str, int base) {
    int rem;
    int i = 0;
    bool is_negative = false;

    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (value < 0 && base == 10) {
        is_negative = true;
        value = -value;
    }
    while (value) {
        rem = value % base;
        str[i++] = rem > 9 ? rem - 10 + 'A' : rem + '0';
        value /= base;
    }
    if (is_negative) str[i++] = '-';
    str[i] = '\0';
    reverse(str);
    return str;
}

void reverse(char *str) {
    int temp;
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}