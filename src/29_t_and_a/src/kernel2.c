#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "libc/stdarg.h"
#include <multiboot2.h>
// #include "gdt.h"
// #include "idt.h"
#include "display/print.h"
#include "gdtv2.h"
#include "idtv2.h" 
#include "vga.h" 
#include "bios_cursor.h" 

extern uint32_t end; // This is defined in arch/i386/linker.ld

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


char * itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

void write_string(int colour, const char *string, int row, int col) {
    volatile char *video = (volatile char*)0xB8000;
    
    // Calculate the starting position in the buffer
    video += (row * 80 + col) * 2;

    while (*string != 0) {
        char ch = *string;
        if ((ch >= 32 && ch <= 126) || (ch >= 128 && ch <= 255) || ch == '\n' || ch == '\t' || ch == '\r') {
            // Printable ASCII characters, extended ASCII characters, or special characters
            if (ch == '\n') {
                // Move to the next line
                row++;
                video = (volatile char*)0xB8000 + (row * 80) * 2;
            } else {
                // Write the character to the buffer
                *video++ = ch;
                *video++ = colour;
            }
            // Check if the cursor reached the end of the screen
            if (video >= (volatile char*)0xB8000 + 80 * 25 * 2) {
                // Reset to the beginning of the screen
                video = (volatile char*)0xB8000;
                row = 0;
            }
        } else if (ch >= '0' && ch <= '9') {
            // Convert integer to string and print
            char buffer[16]; // Adjust size as needed
            int value = ch - '0';
            itoa(value, buffer, 10); // Assuming base 10
            for (int i = 0; buffer[i]; i++) {
                *video++ = buffer[i];
                *video++ = colour;
            }
        } else {
            // Handle non-printable characters or unsupported cases
        }
        string++;
    }
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}



void vga_printf(int color, int row, int col, const char* format, ...) {
    // Start parsing the format string and its arguments
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++; // Move to the next character after '%'

            // Handle format specifiers
            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    char buffer[16]; // Adjust size as needed
                    itoa(value, buffer, 10); // Convert integer to string
                    write_string(color, buffer, row, col);
                    col += strlen(buffer);
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char*);
                    write_string(color, value, row, col);
                    col += strlen(value);
                    break;
                }
                // Add more format specifiers as needed

                default:
                    // Handle unsupported format specifiers
                    break;
            }
        } else {
            // Regular character, print it and move to the next column
            char ch[2] = {*format, '\0'};
            write_string(color, ch, row, col);
            col++;
        }
        format++; // Move to the next character in the format string
    }

    // Clean up the argument list
    va_end(args);
}


int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    // i686_GDT_Initialize();  
    // i686_IDT_Initialize();
    // init_gdt();
    // init_idt();
    //gdt_memory_test();
    //idt_test();
    // Call cpp kernel_main (defined in kernel.cpp)
    // Enable the cursor with start scanline 0 and end scanline 15

    write_string(COLOR_WHITE, "Hello, World!", 0, 0); // Print "Hello, World!" starting from row 0, column 0
    write_string(COLOR_CYAN, "Welcome to VGA text mode!", 1, 10); // Print "Welcome to VGA text mode!" starting from row 1, column 0

    int row = 4;
    int col = 0;

    // Print a string
    vga_printf(COLOR_WHITE, row, col, "Hello, ");
    col += 7; // Update column position

    // Print an integer
    int num = 123;
    vga_printf(COLOR_CYAN, row, col, "%d", num);
    col += 3; // Update column position
    // Print a newline
    row++;
    col = 0;

    // Print a formatted string
    char name[] = "Number of characters";
    vga_printf(COLOR_YELLOW, row, col, "Welcome, number of ch: %d!", strlen(name));
    
    //int test = 0/0;

    //asm volatile ("int $0x2");

    // Move the cursor to row 5, column 10
    //move_cursor(10, 10);

    // Disable the cursor
    // disable_cursor();
    return kernel_main();
}