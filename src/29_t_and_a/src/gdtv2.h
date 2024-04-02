#pragma once

// Include necessary standard library headers
#include "libc/stdint.h" 


// Define the number of GDT entries
#define GDT_ENTRIES 5


// Definition of a GDT entry structure
struct gdt_entry {
  uint16_t limit_low;     // Lower 16 bits of the segment limit (size)
  uint16_t base_low;      // Lower 16 bits of the segment base address
  uint8_t base_middle;    // Middle 8 bits of the segment base address
  uint8_t access;         // Access byte specifying access rights and type
  uint8_t granularity;    // Granularity byte specifying segment size and granularity
  uint8_t base_high;      // Upper 8 bits of the segment base address
} __attribute__((packed)); // Ensure structure is packed without padding


// Definition of a GDT pointer structure
struct gdt_ptr {
  uint16_t limit;        // Size of the GDT in bytes - 1
  uint32_t base;         // Base address of the GDT
} __attribute__((packed)); // Ensure structure is packed without padding


// Function prototypes for initializing and managing the Global Descriptor Table (GDT)

// Initializes the GDT
void init_gdt();
// Loads the GDT pointer into the GDTR register
void gdt_load(struct gdt_ptr *gdt_ptr);
// Sets a descriptor entry in the GDT
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
// Flushes the GDT by loading the GDT pointer and reloading segment registers
void gdt_flush(struct gdt_ptr *gdt_ptr);
