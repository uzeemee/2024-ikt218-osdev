#pragma once

// Include necessary standard library headers
#include "libc/stdint.h" 


#define IDT_ENTRIES 256


// Define the IDT entry structure
struct idt_entry {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t segment;
  uint8_t flags;
  uint16_t base_high;

} __attribute__((packed));


// Define the GDT and IDT pointers
struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));


// Define the structure for interrupt handlers
struct int_handler {
    void (*handler)(void *);  // Function pointer for interrupt handler
    int num;
    void * data;
};


void init_idt();
// Load the GDT and IDT
void idt_load(struct idt_ptr *idt_ptr);
// Define an interrupt handler
void interrupt_handler();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
#define IRQ_COUNT 16

static inline void outb(unsigned short port, unsigned char value);