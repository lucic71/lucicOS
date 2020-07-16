#ifndef PMM_INTERNALS_H_
#define PMM_INTERNALS_H_

#define BLOCKS_PER_DWORD 32
#define BLOCK_SIZE       4096
#define BLOCK_ALIGN      BLOCK_SIZE

/* Macros for testing and aligning memory. */

#define IS_ALIGNED(addr, align) !((addr) & ~((align) - 1))
#define ALIGN(addr, align) (((addr) & ~((align) - 1)) + (align))

/* Macros for converting between units of measure. */

#define KB_TO_BLOCKS(x) (((x) * 1024) / BLOCK_SIZE)

/*
 * Internal variables:
 *
 * mem_size     - Size of availabe memory in KB
 * used_blocks  - Number of used blocks of size BLOCK_SIZE
 * max_blocks   - Maximum number of blocks of size BLOCK_SIZE
 * pmmap        - pointer to a data structure containing info about the
 *                  state of each block (Physical Memory Map)
 * pmmap_size   - Number of double words occupied by pmmap
 *
 */

static size_t   mem_size;
static uint32_t used_blocks;
static uint32_t max_blocks;
static uint32_t *pmmap;
static size_t   pmmap_size;

#endif
