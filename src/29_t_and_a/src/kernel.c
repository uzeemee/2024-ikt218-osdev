#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
// #include "gdt.h"
// #include "idt.h"
#include "display/print.h"
#include "gdtv2.h"
#include "idtv2.h" 
#include "vga.h" 

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




int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    // i686_GDT_Initialize();  
    // i686_IDT_Initialize();
    init_gdt();
    init_idt();
    //gdt_memory_test();
    //idt_test();
    // Call cpp kernel_main (defined in kernel.cpp)
    write_string(COLOR_WHITE, "Hello, World!", 0, 0); // Print "Hello, World!" starting from row 0, column 0
    write_string(COLOR_CYAN, "Welcome to VGA text mode!", 1, 10); // Print "Welcome to VGA text mode!" starting from row 1, column 0
    return kernel_main();
}