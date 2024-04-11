#pragma once
#include "libc/stdint.h"
#include "libc/stddef.h"

// Color codes
#define COLOR_BLACK      0
#define COLOR_BLUE       1
#define COLOR_GREEN      2
#define COLOR_CYAN       3
#define COLOR_RED        4
#define COLOR_PURPLE     5
#define COLOR_BROWN      6
#define COLOR_GRAY       7
#define COLOR_DARK_GRAY  8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED  12
#define COLOR_LIGHT_PURPLE 13
#define COLOR_YELLOW     14
#define COLOR_WHITE      15

// RGB Values
#define RGB_BLACK       0, 0, 0
#define RGB_BLUE        0, 0, 170
#define RGB_GREEN       0, 170, 0
#define RGB_CYAN        0, 170, 170
#define RGB_RED         170, 0, 0
#define RGB_PURPLE      170, 0, 170
#define RGB_BROWN       170, 85, 0
#define RGB_GRAY        170, 170, 170
#define RGB_DARK_GRAY   85, 85, 85
#define RGB_LIGHT_BLUE  85, 85, 255
#define RGB_LIGHT_GREEN 85, 255, 85
#define RGB_LIGHT_CYAN  85, 255, 255
#define RGB_LIGHT_RED   255, 85, 85
#define RGB_LIGHT_PURPLE 255, 85, 255
#define RGB_YELLOW      255, 255, 85
#define RGB_WHITE       255, 255, 255

// Hex Values
#define HEX_BLACK       0x000000
#define HEX_BLUE        0x0000AA
#define HEX_GREEN       0x00AA00
#define HEX_CYAN        0x00AAAA
#define HEX_RED         0xAA0000
#define HEX_PURPLE      0xAA00AA
#define HEX_BROWN       0xAA5500
#define HEX_GRAY        0xAAAAAA
#define HEX_DARK_GRAY   0x555555
#define HEX_LIGHT_BLUE  0x5555FF
#define HEX_LIGHT_GREEN 0x55FF55
#define HEX_LIGHT_CYAN  0x55FFFF
#define HEX_LIGHT_RED   0xFF5555
#define HEX_LIGHT_PURPLE 0xFF55FF
#define HEX_YELLOW      0xFFFF55
#define HEX_WHITE       0xFFFFFF

#define MAX_CHARACTERS_PER_ROW 50 
#define TEXT_COLOR COLOR_GREEN

#define width 80
#define height 25

void print(const char* s, ...);
void scrollUp();
void newLine();
void Reset();

size_t strlen(const char* str);
char* itoa(int value, char* str, int base);
void write_string(int colour, const char *string, int row, int col);
void vga_printf(int color, int row, int col, const char* format, ...);
void int_to_hex(int value, char* buffer);
void int_to_str(int value, char* buffer);
void printf(const char* format, ...);
void reset_print();