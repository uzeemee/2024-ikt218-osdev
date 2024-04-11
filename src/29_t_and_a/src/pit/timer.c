// timer.c -- Initialises the PIT, and handles clock updates.
// Written for JamesM's kernel development tutorials.

#include "timer.h"
#include "../gdt/isr.h"
#include "../vga/vga.h"

uint32_t tick = 0;

static void outb(uint16_t Port, uint8_t Value);
static uint8_t inb(uint16_t port);


static void timer_callback(registers_t regs)
{
   tick++;
   printf("Tick: %d", tick);
}

void init_timer(uint32_t frequency)
{
   // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, &timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   uint32_t divisor = 1193180 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}

static void outb(uint16_t Port, uint8_t Value){
    asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}




//Defines the timer_handler function to be called by the IRQ0 handler.
static void timer_handler(registers_t regs)
{
    //Increment the tick count
    tick++;
    //Toggle the cursor on and off by XORing the cursor end register with 0x80.
    uint8_t cursor_end = inb(0x3D5);
    //Set the register index to the cursor end register.
    outb(0x3D4, 0x0B);
    //Write the XORed value to the register
    outb(0x3D5, cursor_end ^ 0x80);
}

//Function that initializes the Programmable Interval Timer (PIT) with the specified frequency
void init_pit()
{
    //Registers our timer_handler function as the handler for IRQ0
    register_interrupt_handler(IRQ0, &timer_handler);

    //The value we send to the PIT is the value to divide it's input clock
    //(1193180 Hz) by, to get our required frequency. Important to note is
    //that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = DIVIDER;

    //Send the command byte to the PIT command port.
    outb(PIT_CMD_PORT, 0x36);

    //Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor>>8) & 0xFF );

    //Send the frequency divisor bytes to the PIT channel 0 data port.
    outb(PIT_CHANNEL0_PORT, low);
    outb(PIT_CHANNEL0_PORT, high);
}

//Function that returns the current tick count.
uint32_t get_current_tick()
{
    return tick;
}

//Sleep using interrupts for the specified number of milliseconds.
void sleep(uint32_t milliseconds)
{
    uint32_t current_tick = get_current_tick();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t end_ticks = current_tick + ticks_to_wait;

    //Wait for the desired number of ticks to pass
    while (current_tick < end_ticks)
    {
        //Enable interrupts and hald the cpu until the next interrupt occurs.
        asm volatile(
            "sti\n\t" 
            "hlt\n\t" 
        );
        //Update the current tick count.
        current_tick = get_current_tick();
        //printf("%d", current_tick);
    }
    
}

static uint8_t inb(uint16_t port) {
    uint8_t result;
    // Read from the specified port using inline assembly
    asm volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}