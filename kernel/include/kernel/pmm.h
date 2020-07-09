#ifndef PMM_H_
#define PMM_H_

#include "kernel/multiboot.h"

#include <stdint.h>
#include <stddef.h>

/* The only supported block size is 4KB. */

/*
 * pmm_init:
 *  Initializes the Physical Memory Manager.
 *
 * @param size - Size of available physical memory
 * @param mmap_addr - Physical memory address of memory map data structure
 *
 */

void pmm_init(size_t size, uint32_t mmap_addr);

/*
 * pmm_init_region:
 *  Initializes a memory region of specified size.
 *
 * @param base - Base address for region
 * @param size - Size of region
 *
 */

void pmm_init_region(uint32_t base, size_t size);

/*
 * pmm_deinit_region:
 *  Deinitializes a memory region of specified size.
 *
 * @param base - Base address for region
 * @param size - Size of region
 *
 */

void pmm_deinit_region(uint32_t base, size_t size);

/*
 * pmm_alloc_block:
 *  Allocates a memory block and returns a generic pointer to its physical
 *  address.
 *
 */

void *pmm_alloc_block(void);

/*
 * pmm_free_block:
 *  Frees a memory block.
 *
 */

void pmm_free_block(void *p);

/*
 * print_memory_map
 *  Using the multiboot structure, print memory regions, size
 *  of physical memory.
 *
 * @param mb_info - Multiboot info
 *
 */

void print_memory_map(multiboot_memory_map_t *mmap, multiboot_memory_map_t *mmap_end);

/*
 * print_ksections
 *  Print the layout of the kernel in memory.
 *
 */

void print_kernel_map(void);

#endif
