#include <io.h>
#include <isr.h>
#include <stdio.h>

isr_t ISR::m_int_handlers[256];

void ISR::RegisterHandler(uint8_t n, isr_t handler)
{
    m_int_handlers[n] = handler;
}

void ISR::NotResolved(registers_t regs)
{
    printf("unresolved interrupt: %d\n", regs.int_no);
}

isr_t ISR::GetHandler(uint8_t n)
{
    if (m_int_handlers[n] != nullptr)
    {
        return m_int_handlers[n];
    }
}

extern "C"
{
void isr_handler(registers_t regs)
{
   isr_t h = ISR::GetHandler(regs.int_no);
   if (!h)
   {
       printf("test: %d", 2312);
   }
   h(regs);
}

void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       port_writeb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   port_writeb(0x20, 0x20);
   
   isr_t handler = ISR::GetHandler(regs.int_no);
   handler(regs);
}
}
