#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "libc/stdarg.h"
#include <multiboot2.h>
#include "vga/vga.h" 

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    init_gdt();
    
    // i686_GDT_Initialize();  
    // i686_IDT_Initialize();
    // init_idt();
    //gdt_memory_test();
    //idt_test();
    // Call cpp kernel_main (defined in kernel.cpp)
    // Enable the cursor with start scanline 0 and end scanline 15


    int t0 = 0;
    uint32_t t1 = 1;
    uint32_t t2 = 2;
    printf("Allocated %d bytes from 0x%x to 0x%x\n", 0, 1, 2);;
    return kernel_main();
}