#include "print.h"
#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"

void write_character(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
     uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile uint16_t * where;
     where = (volatile uint16_t *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
}

void init_colors(struct TextColors *colors){
    colors->black = 0;
    colors->blue = 1;
    colors->green = 2;
    colors->cyan = 3;
    colors->red = 4;
    colors->magenta = 5;
    colors->brown = 6;
    colors->lightGrey = 7;
    colors->darkGrey = 8;
    colors->lightBlue = 9;
    colors->lightGreen = 10;
    colors->lightCyan = 11;
    colors->lightRed = 12;
    colors->lightMagenta = 13;
    colors->lightBrown = 14;
    colors->white = 15;

}