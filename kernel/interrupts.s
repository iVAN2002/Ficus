.macro ISR_NOERRORCODE code
  .global isr\code
  isr\code:
    cli
    push 0
    push \code
    jmp isr_common_stub
.endm

.macro ISR_ERRORCODE code
  .global isr\code
  isr\code:
    cli
    push \code
    jmp isr_common_stub
.endm

.macro IRQ num1 num2
  .global irq\num1
  irq\num1:
    cli
    push 0
    push \num2
    jmp irq_common_stub
.endm

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8
ISR_NOERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 31

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

/*
    This is our common ISR stub. It saves the processor state, sets
    up for kernel mode segments, calls the C-level fault handler,
    and finally restores the stack frame.
*/
isr_common_stub:
    pusha                    // Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    
    movw %ds, %ax               // Lower 16-bits of eax = ds.
    push %eax                 // save the data segment descriptor
    
    
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    
    call isr_handler
    
    pop %eax        // reload the original data segment descriptor
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    
    popa                     // Pops edi,esi,ebp...
    add $8, %esp     // Cleans up the pushed error code and pushed ISR number
    sti
    iret           // pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

irq_common_stub:
    pusha                    // Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    
    movw %ds, %ax               // Lower 16-bits of eax = ds.
    push %eax                 // save the data segment descriptor
    
    
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    
    call irq_handler
    
    pop %eax        // reload the original data segment descriptor
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    
    popa                     // Pops edi,esi,ebp...
    add $8, %esp     // Cleans up the pushed error code and pushed ISR number
    sti
    iret           // pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
