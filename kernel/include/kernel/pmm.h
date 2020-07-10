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
 * @param mmap_addr - Physical memory address of memory map data structure
 * @param size      - Size of available physical memory in KB
 *
 */

void pmm_init(uint32_t mmap_addr, size_t size);

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
 * pmm_init_available_regions:
 * ---------------------------
 *
 *  Using multiboot info, initialize the available memory regions.
 *
 * @param mmap - Pointer to start of memory map info
 * @param mmap_end - Pointe rto end of memory map info
 *
 */

void pmm_init_available_regions(uint32_t mmap_, uint32_t mmap_end_);

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
 * pmm_deinit_kernel:
 *  Deinitializes the memory where the kernel and the memory map data
 *  structure stay. It assumes that the memory map is placed after
 *  the end of kernel.
 *
 */

void pmm_deinit_kernel(void);

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
 * @param p - Pointer to be free'd
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

void print_memory_map(uint32_t mmap_, uint32_t mmap_end_);

/*
 * print_ksections
 *  Print the layout of the kernel in memory.
 *
 */

void print_kernel_map(void);

#endif
