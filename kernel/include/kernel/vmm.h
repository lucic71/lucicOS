#ifndef VMM_H_
#define VMM_H_

/*
 * vmm_init:
 *  Initialize the Virtual Memory Manager.
 *
 */

void vmm_init(void);

/*
 * vmm_ptable_search:
 *  Given a virtual address, search for its corresponding entry
 *  in Page Table.
 *
 * @param ptable    - Pointer to the beginning of the Page Table
 * @param virt_addr - Virtual address
 *
 * @return - Pointer to corresponding Page Table entry
 *
 */

uint32_t *vmm_ptable_search(uint32_t *ptable, uint32_t virt_addr);

/*
 * vmm_pdir_search:
 *  Given a virtual address, search for its corresponding entry
 *  in Page Directory.
 *
 * @param pdir      - Pointer to the beginning of the Page Directory
 * @param virt_addr - Virtual address
 *
 * @return - Pointer to corresponding Page Directory entry
 *
 */

uint32_t *vmm_pdir_search(uint32_t *pdir, uint32_t virt_addr);

/*
 * vmm_install_pdir:
 *  Install a Page Directory.
 *
 * @param pdir - Pointer to a Page Directory
 *
 */

void vmm_install_pdir(uint32_t *pdir);

/*
 * vmm_flush_tlb:
 *  Flush the Translation Lookaside Buffer.
 *
 * @param virt_tlb - Virtual address of TLB
 *
 */

void vmm_flush_tlb(uint32_t virt_tlb);

/*
 * vmm_map_page:
 *  Maps physical address to virtual address.
 *
 * @param phys - Physical address
 * @param virt - Virtual address
 *
 */

void vmm_map_addr(uint32_t phys, uint32_t virt);

#endif
