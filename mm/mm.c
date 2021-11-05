/*
 * Copyright (c) 2021 Ant Group
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdio.h>
#include <multiboot.h>
#include <errno.h>

extern const void kernel_start;
extern const void kernel_end;

static inline void mb(void) { asm volatile("mfence":::"memory"); }

#if 0
static int mem_test(uint64_t start, uint64_t end)
{
	int ret = 0;
	uint64_t i;
	uint8_t *buf = 0;

	if (start <= &kernel_end)
		start = &kernel_end;

	kprintf("Test region 0x%zx - 0x%zx\n", start, end);

	for (i = start; i < end; i ++) {
		uint8_t w = i & 0xff;

		kprintf("Test addr 0x%zx\n", i);
		buf[i] = w;
		mb();
		if (buf[i] != w) {
			kprintf("Memory addr 0x%zx write fail\n", i);
			ret = -EIO;
			goto out;
		}
	}

	kprintf("Test region 0x%zx - 0x%zx done\n", start, end);
out:
	return ret;
}
#endif

int
mm_init(void)
{
	int ret = -EINVAL;

	kprintf("Kernel start 0x%zx end 0x%zx\n", &kernel_start, &kernel_end);

	if (!mb_info || !(mb_info->flags & MULTIBOOT_INFO_MEM_MAP)) {
		kprintf("%s: cannot get mb_info memmap\n", __func__);
		goto out;
	}

	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) ((size_t) mb_info->mmap_addr);
	multiboot_memory_map_t* mmap_end = (void*) ((size_t) mb_info->mmap_addr + mb_info->mmap_length);

	// mark available memory as free
	while (mmap < mmap_end) {
		if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
			kprintf("Free region 0x%zx - 0x%zx\n", mmap->addr, mmap->addr + mmap->len);
			//mem_test(mmap->addr, mmap->addr + mmap->len);
		}
		mmap = (multiboot_memory_map_t*) ((size_t) mmap + sizeof(uint32_t) + mmap->size);
	}

	ret = 0;
out:
	return ret;
}
