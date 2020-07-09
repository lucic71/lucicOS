#include "kernel/pmm.h"
#include "kernel/multiboot.h"

#include <stdio.h>
#include <stdint.h>

/* Defined in kernel/multiboot.h as macros. */

static char *mem_types[] = {

    "(Available)",
    "(Reserved)",
    "(ACPI Reclaimable)",
    "(ACPI NVS)",
    "(BadRAM)"

};

/*
 * print_memory_map:
 * -----------------
 *
 *  Extract mmap_addr from mb_info and iterate through all avaialble
 *  memory zones.
 *
 */

void print_memory_map(multiboot_memory_map_t *mmap, multiboot_memory_map_t *mmap_end) {

    printf("Physical Memory Map:\n");

    for (int i = 0; mmap < mmap_end; mmap++, i++) {

        printf("region: %d start: 0x%x length: 0x%x type: %d ", i,
                (uint32_t) mmap->addr, (uint32_t) mmap->len, mmap->type);
        printf("%s\n", mem_types[mmap->type - 1]);

    }

}
