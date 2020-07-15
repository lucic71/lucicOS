.global enable_paging

/*
 * enable_paging:
 * --------------
 *
 *  Move the argument in cr3 and enable PE and PG bits in cr0.
 *
 */

enable_paging:

    mov 0x04(%esp), %eax
    mov %eax, %cr3

    mov %cr0, %eax
    or $0x80000001, %eax
    mov %eax, %cr0

    ret
