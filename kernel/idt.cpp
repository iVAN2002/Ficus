#include <idt.h>
#include <string.h>
#include <io.h>

idt_entry_t IDT::m_idt_entries[256];
idt_ptr_t   IDT::m_idt_ptr;

extern "C"
{
    extern void idt_flush(uint32_t);
    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr31();
    
    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();
}

void IDT::Init()
{
    m_idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    m_idt_ptr.base  = (uint32_t)&m_idt_entries;
 
    memset(&m_idt_entries, 0, sizeof(idt_entry_t)*256);
    
    port_writeb(0x20, 0x11);
    port_writeb(0xA0, 0x11);
    port_writeb(0x21, 0x20);
    port_writeb(0xA1, 0x28);
    port_writeb(0x21, 0x04);
    port_writeb(0xA1, 0x02);
    port_writeb(0x21, 0x01);
    port_writeb(0xA1, 0x01);
    port_writeb(0x21, 0x0);
    port_writeb(0xA1, 0x0);
 
    _SetGate(0, (uint32_t)isr0 , 0x08, 0x8E);
    _SetGate(1, (uint32_t)isr1 , 0x08, 0x8E);
    _SetGate(2, (uint32_t)isr2 , 0x08, 0x8E);
    _SetGate(3, (uint32_t)isr3 , 0x08, 0x8E);
    _SetGate(4, (uint32_t)isr4 , 0x08, 0x8E);
    _SetGate(5, (uint32_t)isr5 , 0x08, 0x8E);
    _SetGate(6, (uint32_t)isr6 , 0x08, 0x8E);
    _SetGate(7, (uint32_t)isr7 , 0x08, 0x8E);
    _SetGate(8, (uint32_t)isr8 , 0x08, 0x8E);
    _SetGate(9, (uint32_t)isr9 , 0x08, 0x8E);
    _SetGate(10, (uint32_t)isr10 , 0x08, 0x8E);
    _SetGate(11, (uint32_t)isr11 , 0x08, 0x8E);
    _SetGate(12, (uint32_t)isr12 , 0x08, 0x8E);
    _SetGate(13, (uint32_t)isr13 , 0x08, 0x8E);
    _SetGate(14, (uint32_t)isr14 , 0x08, 0x8E);
    _SetGate(15, (uint32_t)isr15 , 0x08, 0x8E);
    _SetGate(16, (uint32_t)isr16 , 0x08, 0x8E);
    _SetGate(17, (uint32_t)isr17 , 0x08, 0x8E);
    _SetGate(18, (uint32_t)isr18 , 0x08, 0x8E);
    _SetGate(19, (uint32_t)isr19 , 0x08, 0x8E);
    _SetGate(31, (uint32_t)isr31 , 0x08, 0x8E);
    _SetGate(32, (uint32_t)irq0 , 0x08, 0x8E);
    _SetGate(33, (uint32_t)irq1 , 0x08, 0x8E);
    _SetGate(34, (uint32_t)irq2 , 0x08, 0x8E);
    _SetGate(35, (uint32_t)irq3 , 0x08, 0x8E);
    _SetGate(36, (uint32_t)irq4 , 0x08, 0x8E);
    _SetGate(37, (uint32_t)irq5 , 0x08, 0x8E);
    _SetGate(38, (uint32_t)irq6 , 0x08, 0x8E);
    _SetGate(39, (uint32_t)irq7 , 0x08, 0x8E);
    _SetGate(40, (uint32_t)irq8 , 0x08, 0x8E);
    _SetGate(41, (uint32_t)irq9 , 0x08, 0x8E);
    _SetGate(42, (uint32_t)irq10 , 0x08, 0x8E);
    _SetGate(43, (uint32_t)irq11 , 0x08, 0x8E);
    _SetGate(44, (uint32_t)irq12 , 0x08, 0x8E);
    _SetGate(45, (uint32_t)irq13 , 0x08, 0x8E);
    _SetGate(46, (uint32_t)irq14 , 0x08, 0x8E);
    _SetGate(47, (uint32_t)irq15 , 0x08, 0x8E);
 
    idt_flush((uint32_t)&m_idt_ptr);
}

void IDT::_SetGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
   m_idt_entries[num].base_lo = base & 0xFFFF;
   m_idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   m_idt_entries[num].sel     = sel;
   m_idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   m_idt_entries[num].flags   = flags /* | 0x60 */;
}
