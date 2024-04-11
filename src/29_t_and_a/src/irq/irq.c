#include "irq.h"
#include "../utils/util.h"
#include "../idt/idt.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "../vga/vga.h"
// Array to store IRQ handlers
void (*irq_handlers[IRQ_COUNT])(void);

// Initialize IRQ handlers
void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i] = NULL;
    //register_irq_handler(i, irq_handler);
  }
}

// Register an IRQ handler
void register_irq_handler(int irq, void (*handler)(void)) {
  irq_handlers[irq] = handler;
}

// The main IRQ handler
void irq_handler(int irq) {
  // Check if a handler is registered for this IRQ
  if (irq_handlers[irq] != NULL) {
    irq_handlers[irq]();
    printf("got irq #%d", irq);
  }

  // Send an EOI (End of Interrupt) signal to the PIC (Programmable Interrupt Controller)
  if (irq >= 8) {
    // Send EOI to the slave PIC
    outPortB(0xA0, 0x20);
  }
  // Send EOI to the master PIC
  outPortB(0x20, 0x20);
}
