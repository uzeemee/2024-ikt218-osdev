#ifndef BIOS_CURSOR_H
#define BIOS_CURSOR_H

extern void enable_cursor();
extern void disable_cursor();
extern void move_cursor(unsigned char row, unsigned char column);
extern void get_cursor_data(unsigned char *start_scanline, unsigned char *end_scanline, unsigned char *row, unsigned char *column);

#endif /* BIOS_CURSOR_H */

