#include "../vga/vga.h"
#include "isr.h"

static void outb(uint16_t Port, uint8_t Value);

char* exception_messages[] = {
    "Division By Zero",             // 0
    "Debug",                        // 1
    "Non Maskable Interrupt",       // 2
    "Breakpoint",                   // 3
    "Into Detected Overflow",       // 4
    "Out of Bounds",                // 5
    "Invalid Opcode",               // 6
    "No Coprocessor",               // 7
    "Double fault",                 // 8
    "Coprocessor Segment Overrun",  // 9
    "Bad TSS",                      // 10
    "Segment not present",          // 11
    "Stack fault",                  // 12
    "General protection fault",     // 13
    "Page fault",                   // 14
    "Unknown Interrupt",            // 15
    "Coprocessor Fault",            // 16
    "Alignment Fault",              // 17
    "Machine Check",                // 18
    "Reserved",                     
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    if (regs.int_no < 32){
        printf("recieved interrupt: #%d - %s", regs.int_no, exception_messages[regs.int_no]);
    }

    else{
        printf("recieved interrupt: #%d", regs.int_no);
    }
}

isr_t interrupt_handlers[256];

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}


void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

static void outb(uint16_t Port, uint8_t Value){
    asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}

// Array to store IRQ handlers
void (*irq_handlers[IRQ_COUNT])(void);

// Initialize IRQ handlers
void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i] = NULL;
  }
}