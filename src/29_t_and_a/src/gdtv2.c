#include "gdtv2.h" 
// Include necessary standard library headers
#include "libc/stdint.h"

// Define global variables
struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdt_ptr;


void init_gdt() {
    // Set the GDT limit    
    gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
    gdt_ptr.base = (uint32_t) &gdt;

    // num, base, limit, access, granularity 
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    // Load the GDT
    gdt_load(&gdt_ptr);

    // Flush GDT pointer
    gdt_flush((uint32_t)&gdt_ptr);
}


// Loads the Global Descriptor Table (GDT) pointer into the GDTR register
void gdt_load(struct gdt_ptr *gdt_ptr) {
    // Use inline assembly to load the GDT pointer into the GDTR register
    asm volatile("lgdt %0" : : "m" (*gdt_ptr));
}


// Sets a descriptor entry in the Global Descriptor Table (GDT)
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // Calculate and assign the base address of the segment
    gdt[num].base_low    = (base & 0xFFFF);                  // Lower 16 bits of base
    gdt[num].base_middle = (base >> 16) & 0xFF;              // Middle 8 bits of base
    gdt[num].base_high   = (base >> 24) & 0xFF;              // Upper 8 bits of base

    // Assign the limit of the segment and its granularity
    gdt[num].limit_low   = (limit & 0xFFFF);                 // Lower 16 bits of limit
    gdt[num].granularity = (limit >> 16) & 0x0F;             // Upper 4 bits of limit

    // Assign access rights and type information to the segment
    gdt[num].granularity |= gran & 0xF0;                     // Granularity bits
    gdt[num].access      = access;                           // Access byte
}


void gdt_flush(struct gdt_ptr *gdt_ptr) {
    // Load the GDT pointer into the gdtr register
    asm volatile("lgdt %0" : : "m" (*gdt_ptr));
    // Reload segment registers to update them with the new GDT
    asm volatile(
        "mov $0x10, %ax\n\t" // Load the data segment selector into ax
        "mov %ax, %ds\n\t"   // Reload the data segment register
        "mov %ax, %es\n\t"   // Reload the extra segment register
        "mov %ax, %fs\n\t"   // Reload the fs segment register
        "mov %ax, %gs"       // Reload the gs segment register
    );
}