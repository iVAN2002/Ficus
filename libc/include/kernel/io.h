#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include <stdint.h>

uint8_t port_readb(uint16_t port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

uint16_t port_readw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void port_writeb(uint16_t port, uint8_t data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

#endif
