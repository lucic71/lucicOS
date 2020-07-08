#ifndef PMM_H_
#define PMM_H_

#include "kernel/multiboot.h"

/*
 * print_memory_map
 *  Using the multiboot structure, print memory regions, size
 *  of physical memory and info about kernel sections.
 *
 * @param mb_info - Multiboot info
 *
 */

void print_memory_map(multiboot_info_t *mb_info);

#endif
