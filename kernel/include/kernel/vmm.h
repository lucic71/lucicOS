#ifndef VMM_H_
#define VMM_H_

#include <stdint.h>

/*
 * vmm_init:
 *  Initialize the Virtual Memory Manager. At the moment it does not
 *  support Higher Half Kernel. It just identity-maps the first 4MB
 *  of physical memory.
 *
 */

void vmm_init(void);

/*
 * vmm_map_page:
 *  Maps physical address to virtual address. This routine must be called
 *  only after paging was enabled (aka after vmm_init).
 *
 * @param phys - Physical address
 * @param virt - Virtual address
 *
 */

int vmm_map_addr(uint32_t phys, uint32_t virt);

/*
 * vmm_unmap_page:
 *  Unmaps a virtual address. This routine must be called only after paging
 *  was enabled (aka after vmm_init).
 *
 * @param virt - Virtual address
 *
 */

void vmm_unmap_addr(uint32_t virt);

#endif
