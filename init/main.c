/*
 * Copyright (c) 2021 Ant Group
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <multiboot.h>
//#include <elf.h>
#include <mm.h>

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

	kprintf("ZheLuo start\n");

	if (mm_init() != 0)
		goto error;

error:
	while(1) { HALT; }
}
