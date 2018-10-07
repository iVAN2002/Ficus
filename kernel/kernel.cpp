#include <tty.h>
#include <gdt.h>
#include <idt.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
	void
	kernel_main(void)
{
	terminal_initialize();
	
	printf("[GDT] Initializing...");
	
	GDT::Init();
	
	printf(" Done\n");
	
	printf("[IDT] Initializing...");
	
	IDT::Init();
	
	printf(" Done\n");
	
	asm volatile ("int $0x3");
}
