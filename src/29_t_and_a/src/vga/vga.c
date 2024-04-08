#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "libc/stdarg.h"
#include "vga.h" 


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
	return  len;
}

void int_to_str(int value, char* buffer) {
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    // Convert each digit to a character
    do {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    } while (value != 0);

    // Add the negative sign if necessary
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    // Null-terminate the string
    buffer[i] = '\0';
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

// Custom function to convert an integer to a hexadecimal string
void int_to_hex(int value, char* buffer) {
    const char* hex_chars = "0123456789ABCDEF";
    buffer[0] = hex_chars[(value >> 28) & 0xF];
    buffer[1] = hex_chars[(value >> 24) & 0xF];
    buffer[2] = hex_chars[(value >> 20) & 0xF];
    buffer[3] = hex_chars[(value >> 16) & 0xF];
    buffer[4] = hex_chars[(value >> 12) & 0xF];
    buffer[5] = hex_chars[(value >> 8) & 0xF];
    buffer[6] = hex_chars[(value >> 4) & 0xF];
    buffer[7] = hex_chars[value & 0xF];
    buffer[8] = '\0';
}

// Custom printf function
void printf(const char* format, ...) {
    // Start parsing the format string and its arguments
    va_list args;
    va_start(args, format);

    int row = 0;
    int col = 0;

    while (*format) {
        if (*format == '%') {
            format++; // Move to the next character after '%'

            // Handle format specifiers
            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    char buffer[16]; // Adjust size as needed
                    int_to_str(value, buffer); // Convert integer to string
                    vga_printf(TEXT_COLOR, row, col, buffer);
                    col += strlen(buffer);
                    break;
                }
                case 'x': {
                    int value = va_arg(args, int);
                    char buffer[9]; // Assuming 32-bit integer, adjust size as needed
                    int_to_hex(value, buffer); // Convert integer to hexadecimal string
                    vga_printf(TEXT_COLOR, row, col, buffer);
                    col += strlen(buffer);
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char*);
                    vga_printf(TEXT_COLOR, row, col, value);
                    col += strlen(value);
                    break;
                }
                case 'n': {
                    // Handle newline character
                    row++; // Move to the next row
                    col = 0; // Reset column to the beginning of the row
                    break;
                }
                // Add more format specifiers as needed

                default:
                    // Handle unsupported format specifiers
                    break;
            }
        } else {
            if (*format == '\n') {
                // Handle newline character
                row++; // Move to the next row
                col = 0; // Reset column to the beginning of the row
            } else {
                // Regular character, print it and move to the next column
                char ch[2] = {*format, '\0'};
                vga_printf(TEXT_COLOR, row, col, ch);
                col++;
            }
        }

        // Check if we need to switch rows
        if (col >= MAX_CHARACTERS_PER_ROW) {
            col = 0;
            row++;
        }

        format++; // Move to the next character in the format string
    }

    // Clean up the argument list
    va_end(args);
}