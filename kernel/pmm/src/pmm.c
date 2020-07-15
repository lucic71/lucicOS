#include "kernel/pmm.h"

#include "pmm_internals.h"

#include "lib/bitmap.h"

#include <string.h>
#include <stddef.h>

/*
 * pmm_init:
 * ---------
 *
 *  Set the internal variables and initialize the pmmap data type.
 *  It initializes all memory zones as used by settings all bits in pmmap.
 *  At the moment, pmmap is a bitmap.
 *
 */

void pmm_init(uint32_t pmmap_addr, size_t size) {

    mem_size    = size;
    max_blocks  = KB_TO_BLOCKS(mem_size);
    used_blocks = max_blocks;
    pmmap       = (uint32_t *) pmmap_addr;

    pmmap_size = mem_size / BLOCKS_PER_BYTE;
    if (mem_size % BLOCKS_PER_BYTE)
        pmmap_size++;

    memset(pmmap, 0xFF, pmmap_size);

}

/*
 * pmm_init_available_regions:
 * ---------------------------
 *
 *  Using multiboot info, it initializes all available memory zones.
 *
 */

void pmm_init_available_regions(uint32_t mmap_, uint32_t mmap_end_) {

    multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) mmap_;
    multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t *) mmap_end_;

    for (int i = 0; mmap < mmap_end; mmap++, i++)
        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
            pmm_init_region((uint32_t) mmap->addr, (size_t) mmap->len);
}

/*
 * pmm_init_region:
 * ----------------
 *
 *  @var blocks - Number of blocks to be unset starting from @align
 *  @var align  - Starting index in bitmap
 *
 */

void pmm_init_region(uint32_t base, size_t size) {

    size_t blocks  = size / BLOCK_SIZE;
    uint32_t align = base / BLOCK_SIZE;

    for (size_t i = 0; i < blocks; i++) {

        bitmap_unset(pmmap, align++);
        used_blocks--;

    }

    bitmap_set(pmmap, 0);

}

/*
 * pmm_deinit_region:
 * ------------------
 *
 *  Sets the corresponding bit in pmmap and increments the number of
 *  used blocks.
 *
 */

void pmm_deinit_region(uint32_t base, size_t size) {

    size_t blocks = size / BLOCK_SIZE;
    uint32_t align = base / BLOCK_SIZE;

    for (size_t i = 0; i < blocks; i++) {

        bitmap_set(pmmap, align++);
        used_blocks++;

    }

}

/*
 * pmm_deinit_kernel:
 * ------------------
 *
 *  Deinitializes the blocks containing the kernel and the memory map. There
 *  is an align operation because the routine tries to deinitialize all
 *  blocks where pmmap may sit in memory.
 *
 */

void pmm_deinit_kernel(void) {

    extern uint8_t *_kernel_start;
    extern uint8_t *_kernel_end;

    size_t kernel_size = (size_t) &_kernel_end - (size_t) &_kernel_start;

    uint32_t pmmap_size_aligned = pmmap_size;
    if (!IS_ALIGNED(pmmap_size_aligned, BLOCK_SIZE))
        pmmap_size_aligned = ALIGN(pmmap_size_aligned, BLOCK_SIZE);

    pmm_deinit_region((uint32_t) &_kernel_start, kernel_size);
    pmm_deinit_region((uint32_t) &_kernel_end, pmmap_size_aligned);

}

/*
 * pmm_alloc_block:
 * ----------------
 *
 *  Searches for a free block and returns a pointer to its physical memory
 *  location.
 *
 */

void *pmm_alloc_block(void) {

    if (used_blocks - max_blocks <= 0)
        return NULL;

    int p_index = bitmap_first_unset(pmmap, max_blocks);

    if (p_index == -1)
        return NULL;

    bitmap_set(pmmap, p_index);
    used_blocks++;

    return (void *) (BLOCK_SIZE * p_index);

}

/*
 * pmm_free_block:
 * ---------------
 *
 *  Checks if p is a valid pointer to free (is not first memory block)
 *  and frees its entry it pmmap.
 *
 */

void pmm_free_block(void *p) {

    if (p == NULL)
        return;

    uint32_t p_addr = (uint32_t) p;

    int index = p_addr / BLOCK_SIZE;
    bitmap_unset(pmmap, index);

    used_blocks--;

}

