/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
	void
	kernel_main(void)
{
	terminal_initialize();

	printf("Hello, kernel World!\n");
}
