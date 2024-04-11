// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H
#include "libc/stdint.h"

void outb(uint16_t port, uint8_t value);
u8int inb(uint16_t port);
u16int inw(uint16_t port);

#endif