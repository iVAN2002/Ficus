/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <string.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
	void
	kernel_main(void)
{
	/* Initialize terminal interface */
        
    //const char *a = "test";
    //size_t b = strlen(a);
	terminal_initialize();

	terminal_writestring("Hello, kernel World!\n");
}
