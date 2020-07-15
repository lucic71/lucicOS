#ifndef VMM_INTERNALS_H_
#define VMM_INTERNALS_H_

#include "pte.h"
#include "pde.h"

/*
 * pd  - Page directory placed in the Physical Memory
 * kpd - Kernel page directory palced in the last 4MB of memory.
 *
 */

static pde_t pd[1024] __attribute__((aligned (4096)));
static pde_t *kpd = (pde_t *) 0xFFFFF000;

/* Start of virtual page tables after pagination was enabled. */

#define VIRT_PT_START 0xFFC00000

/*
 * enable_paging:
 * 
 * @param pd_phys_addr - Physical address of Page Directory.
 *
 */

void enable_paging(uint32_t pd_phys_addr);

#endif
