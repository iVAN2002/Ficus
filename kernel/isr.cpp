#include <isr.h>
#include <stdio.h>

extern "C"
{
void isr_handler(registers_t regs)
{
   printf("unresolved interrupt %d\n", regs.int_no);
}
}
