#ifndef KMAIN_MULTIBOOT_H_
#define KMAIN_MULTIBOOT_H_

#include "kernel/multiboot.h"

#include <stdint.h>

/*
 * multiboot_init
 *  Check whether important information is present in multiboot info structure.
 *  Also check that the magic number is correct.
 *
 * @param mb_info  - Multiboot info structure
 * @param mb_magic - Multiboot magic number
 *
 */

void multiboot_init(multiboot_info_t *mb_info, uint32_t mb_magic);

#endif
