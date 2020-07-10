#include "kernel/multiboot.h"
#include "kmain/multiboot.h"
#include "kernel/log.h"

/*
 * multiboot_init:
 * ---------------
 *
 *  Check flags field in mb_info and check the magic number.
 *
 */

void multiboot_init(multiboot_info_t *mb_info, uint32_t mb_magic) {

    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC)
        panic("Not a multiboot bootloader!");

    if (!mb_info)
        panic("Invalid multiboot pointer");

    if (!(mb_info->flags & MULTIBOOT_INFO_MEMORY))
        panic("There is no memory info in multiboot");

}
