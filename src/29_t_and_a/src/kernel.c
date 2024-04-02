#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
// #include "gdt.h"
// #include "idt.h"
#include "display/print.h"
#include "gdtv2.h"
#include "idtv2.h" 

// Define a test function that relies on GDT memory
void gdt_memory_test() {
    // Define a pointer to access GDT memory
    volatile uint32_t *gdt_memory_ptr = (volatile uint32_t *)0x1000; // Example base address in GDT memory
    
    // Write a value to the GDT memory location
    *gdt_memory_ptr = 0xDEADBEEF; // Example data to write
    
    // Read the value back from the GDT memory location
    uint32_t data_read = *gdt_memory_ptr;
    
    // Check if the read value matches the written value
    if (data_read == 0xDEADBEEF) {
        write_string(4, "PASSED");
        // Test passed
        // Add any additional actions or assertions here
    } else {
        // Test failed
        // Handle the failure scenario
    }
}

void test_interrupt_handler(void *data) {
    write_string(8, "INTERRUPT");
}

// Function to test IDT
void idt_test() {
    // Register the test interrupt handler for a specific interrupt number (e.g., IRQ0)
    register_int_handler(IRQ0, test_interrupt_handler, NULL);

    // Trigger the test interrupt
    int_handler(IRQ0);
}

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

void write_string(int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}




int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    //i686_GDT_Initialize();  
    //i686_IDT_Initialize();
    init_gdt();
    init_gdt();
    gdt_memory_test();
    idt_test();
    // char string[] = "abraham";
    // print(string); // Pass the array, not a string literal
    // Call cpp kernel_main (defined in kernel.cpp)
    write_string(2, "addd");
    return kernel_main();
}