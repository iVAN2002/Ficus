#ifndef _KERNEL_IO_H_
#define _KERNEL_IO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

uint8_t port_readb(uint16_t port);
uint16_t port_readw(uint16_t port);
void port_writeb(uint16_t port, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif
