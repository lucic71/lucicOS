#include "kernel/vmm.h"

#include "vmm_internals.h"

#include "kernel/pmm.h"

#include <string.h>

/*
 * vmm_init:
 * ---------
 *
 *  Allocate the first page table and put in in Page Directory on the
 *  first position (because this routine wants to map the first 4MB of
 *  physical space).
 *
 *  Next, point the last entry of pd to pd. This is called Recursive Mapping.
 *  Its advantage is that the kernel can map pages even after the paging
 *  was enabled. TODO: maybe look for other solutions.
 *
 *  The first page table is then filled with its corresponding addresses and
 *  paging is enabled.
 *
 */

void vmm_init(void) {

    pte_t *first_pt = pmm_alloc_block();

    pde_set_frame(pd, (uint32_t) first_pt);
    pde_set_attr(pd, PDE_PRESENT | PDE_WRITABLE);

    pde_set_frame(pd + 1023, (uint32_t) pd);
    pde_set_attr(pd + 1023, PDE_PRESENT | PDE_WRITABLE);

    memset(first_pt, sizeof(pte_t) * 1024, 0x00);

    for (int x = 0; x < 1024; x++) {
        pte_set_frame(first_pt + x, x * 4096);
        pte_set_attr(first_pt + x, PTE_PRESENT | PDE_WRITABLE);
    }

    enable_paging((uint32_t) pd);

}

/*
 * vmmap_map_addr:
 * ---------------
 *
 *  Paging is now enabled and this routine works with kpd instead of pd.
 *
 *  It checks if there is a corresponding entry for virt in PD. If there
 *  is an entry, it further checks if there is an PT entry for virt. If
 *  there is no entry then it creates one, else it returns -1.
 *
 *  If there is no PD entry, it creates one and also creates a PT entry.
 *
 */

int vmm_map_addr(uint32_t phys, uint32_t virt) {

    int pd_index = PD_INDEX(virt);
    int pt_index = PT_INDEX(virt);

    if (pde_is_present(kpd[pd_index])) {

        uint32_t *pt = (uint32_t *) (VIRT_PT_START + pd_index * 0x1000);
        if (!pte_is_present(pt[pt_index])) {

            pte_set_frame(pt + pt_index, phys);
            pte_set_attr(pt + pt_index, PTE_PRESENT | PTE_WRITABLE);

        } else
            return -1;

    } else {

        pte_t *new_pt_phys = pmm_alloc_block();

        pde_set_frame(kpd + pd_index, (uint32_t) new_pt_phys);
        pde_set_attr(kpd + pd_index, PDE_PRESENT | PDE_WRITABLE);

        pte_t *new_pt_virt = (pte_t *) (VIRT_PT_START + pd_index * 0x1000);

        pte_set_frame(new_pt_virt, phys);
        pte_set_attr(new_pt_virt + pt_index, PTE_PRESENT | PTE_WRITABLE);

    }

    return 0;

}

/*
 * vmm_unmap_addr:
 * ---------------
 *
 *  It finds the corresponding PD and PT entries for virt. It also checks if
 *  the page table that contains virt can be free'd by probing all PTE's available
 *  in the current page table.
 *
 *  If there are 1024 non-present entries then the page table can be freed.
 *
 */

void vmm_unmap_addr(uint32_t virt) {

    int pd_index = PD_INDEX(virt);
    int pt_index = PT_INDEX(virt);

    if (pde_is_present(kpd[pd_index])) {

        pte_t *pt_virt = (pte_t *) (VIRT_PT_START + pd_index * 0x1000);
        if (pte_is_present(pt_virt[pt_index]))
            pt_virt[pt_index] = 0x00;

        int i;
        for (i = 0; i < 1024; i++)
            if (pte_is_present(pt_virt[pt_index]))
                break;

        if (i == 1024) {

            pmm_free_block((void *) pde_get_frame(kpd[pd_index]));
            kpd[pd_index] = 0x00;

        }

    }

}

