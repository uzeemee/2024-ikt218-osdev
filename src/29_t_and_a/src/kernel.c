#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "gdt.h"
#include "idt.h"
#include "display/print.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

void print(char* string) {
    struct TextColors __text_colors__;
    // Assuming you have a function to initialize colors
    init_colors(&__text_colors__);
    int xPosition = 1;                   // X-coordinate on the screen
    int yPosition = 5;                   // Y-coordinate on the screen
    unsigned char foregroundColor = __text_colors__.white;
    unsigned char backgroundColor = __text_colors__.darkGrey;

    for (uint16_t i = 0; string[i] != '\0'; i++) {
        write_character(string[i], foregroundColor, backgroundColor, xPosition + i, yPosition);
    }
}

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    i686_GDT_Initialize();  
    i686_IDT_Initialize();
    char string[] = "abraham";
    print(string); // Pass the array, not a string literal
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}