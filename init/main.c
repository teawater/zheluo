#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <multiboot.h>
#include <elf.h>
#include <page.h>

#define HALT	asm volatile ("hlt")

extern const void kernel_start;
extern const void kernel_end;
extern const void bss_start;
extern const void bss_end;

void main(void)
{
	// initialize .bss section
	memset((void*)&bss_start, 0, ((size_t) &bss_end - (size_t) &bss_start));

	uart_init();

	kprintf("123\n");

	while(1) { HALT; }
}
