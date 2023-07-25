#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <trinity/vga.h>

#define NUM_STR_SIZE (sizeof(int) * 8 + 1)

void kprint(const char *str);
void kprint_num(int num, int base);

#endif