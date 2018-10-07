#include <idt.h>
#include <string.h>

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
}

void IDT::Init()
{
    m_idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    m_idt_ptr.base  = (uint32_t)&m_idt_entries;
 
    memset(&m_idt_entries, 0, sizeof(idt_entry_t)*256);
 
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
