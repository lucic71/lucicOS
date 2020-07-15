#ifndef PTE_H_
#define PTE_H_

#include <stdint.h>

typedef uint32_t pte_t;

/* Macros for working with Page Tables. */

#define PT_TABLE_SIZE 1024
#define PT_INDEX(x) (((x) >> 12) & 0x3FF)

/* Page Table Flags. */

enum PTE_FLAGS { 

    PTE_PRESENT       = 0x01,
    PTE_WRITABLE      = 0x02,
    PTE_USER          = 0x04,
    PTE_WRITETHOUGH	  = 0x08,
    PTE_NOT_CACHEABLE = 0x10,
    PTE_ACCESSED      = 0x20,
    PTE_DIRTY         = 0x40,
    PTE_PAT           = 0x80,
    PTE_CPU_GLOBAL    = 0x100,
    PTE_LV4_GLOBAL    = 0x200,
    PTE_FRAME         = 0xFFFFF000 

};

/* pte_*set_attr:
 *  Set/Unset attribute in Page Table Entry.
 *
 * @param e    - PT entry
 * @param attr - Attribute
 *
 */

static inline void pte_set_attr(pte_t *e, uint32_t attr) { *e |= attr; }
static inline void pte_unset_attr(pte_t *e, uint32_t attr) { *e &= ~attr; }

/*
 * pte_set/get_frame:
 *  Sets/Gets the frame the PTE points to. The physical address must
 *  be 4K aligned
 *
 * @param e         - PT entry
 * @param phys_addr - Frame to be set
 *
 */

static inline void pte_set_frame(pte_t *e, uint32_t phys_addr) {
    *e = (*e & ~PTE_FRAME) | phys_addr;
}
static inline uint32_t pte_get_frame(pte_t e) { return e & PTE_FRAME; }

/* Checkers for flags. */

static inline int pte_is_present(pte_t e) { return e & PTE_PRESENT; }

#endif
