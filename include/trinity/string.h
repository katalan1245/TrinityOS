#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

void *memset(void *str, uint8_t c, size_t n);
void *memmove(void *destination, const void* source, size_t num);
size_t strlen(const char *str);
char *itoa(int value, char *str, int base);
void reverse(char *str);

#endif