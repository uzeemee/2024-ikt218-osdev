#include "libc/stdint.h"
#include "util.h"

void outPortB(uint16_t Port, uint8_t Value){
    asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}

uint8_t inPortB(uint16_t port) {
    uint8_t result;
    // Read from the specified port using inline assembly
    asm volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}