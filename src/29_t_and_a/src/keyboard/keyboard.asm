global keyboard_isr
extern keyboard_handler

section .text
keyboard_isr:
    pusha                      ; Push general-purpose registers
    call keyboard_handler      ; Call C function to handle keyboard input
    popa                       ; Restore general-purpose registers
    iret                       ; Return from interrupt