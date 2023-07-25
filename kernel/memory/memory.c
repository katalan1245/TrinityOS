#include <trinity/memory.h>

void *memset(void *str, int c, size_t n) {
    char *ptr = str;
    while (n--) { 
        *ptr++ = c; 
    }
    return str;
}