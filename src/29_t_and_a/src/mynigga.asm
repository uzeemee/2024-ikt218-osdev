; Enter protected mode    
mov eax, cr0       ; Move the value of CR0 into eax
or eax, 1          ; Set the PE bit in eax
mov cr0, eax       ; Move the modified value back into CR0