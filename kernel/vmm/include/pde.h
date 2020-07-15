#ifndef PDE_H_
#define PDE_H_

#include <stdint.h>

typedef uint32_t pde_t;

/* Macros for working with Page Directories. */

#define PD_TABLE_SIZE 1024
#define PD_INDEX(x) (((x) >> 22) & 0x3FF)

/* Page Directory Flags. */

enum PDE_FLAGS { 

    PDE_PRESENT    = 0x01,
    PDE_WRITABLE   = 0x02,
    PDE_USER       = 0x04,
    PDE_PWT        = 0x08,
    PDE_PCD        = 0x10,
    PDE_ACCESSED   = 0x20,
    PDE_DIRTY      = 0x40,
    PDE_4MB        = 0x80,
    PDE_CPU_GLOBAL = 0x100,
    PDE_LV4_GLOBAL = 0x200,
    PDE_FRAME      = 0xFFFFF000 

};

/* pde_*set_attr:
 *  Set/Unset attribute in Page Directory Entry.
 *
 * @param e    - PD entry
 * @param attr - Attribute
 *
 */

static inline void pde_set_attr(pde_t *e, uint32_t attr) { *e |= attr; }
static inline void pde_unset_attr(pde_t *e, uint32_t attr) { *e &= ~attr; }

/*
 * pde_set/get_frame:
 *  Sets/Gets the frame the PDE points to. The physical address must
 *  be 4K aligned
 *
 * @param e         - PD entry
 * @param phys_addr - Frame to be set
 *
 */


static inline void pde_set_frame(pde_t *e, uint32_t phys_addr) {
    *e = (*e & ~PDE_FRAME) | phys_addr;
}
static inline uint32_t pde_get_frame(pde_t e) { return e & PDE_FRAME; }

/* Checkers for flags. */

static inline int pde_is_present(pde_t e) { return e & PDE_PRESENT; }

#endif
