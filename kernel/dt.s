.global gdt_flush
gdt_flush:
    movl 4(%esp), %eax // Getting a pointer to GDT, passed as a parameter
    lgdt (%eax)
    
    jmp $0x08, $reload
reload:
    movw $0x10, %ax          // 0x10 is the offset in the GDT to our data segment
    movw %ax, %ds             // Load all data segment selectors
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    
    ret

.global idt_flush
idt_flush:
    movl 4(%esp), %eax // Getting a pointer to GDT, passed as a parameter
    lidt (%eax)
    ret
