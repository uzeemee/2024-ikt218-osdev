#include "libc/stdint.h"

void outPortB(uint16_t Port, uint8_t Value);
uint8_t inPortB(uint16_t port);

struct InterruptRegisters{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};