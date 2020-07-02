#include "tables/gdt.h"
#include "tables/a20.h"

.global _start

/* Entry point in the kernel. */

.extern kmain

/*
 * GRUB will load the kernel only if it compiles with the multiboot spec.
 * The header must contain a magic number, a flag (which can be set to 0x00)
 * and the checksum (checksum = - (flag + magic_number))
 *
 */

.set MAGIC_NUMBER, 0x1BADB002
.set FLAGS,        0x00
.set CHECKSUM,     -(MAGIC_NUMBER + FLAGS)



/*
* Put the header in multiboot section so that it is placed in the first 8Kib
* of the executable.
*
*/

.section .multiboot
    .align 4

    .int MAGIC_NUMBER
    .int FLAGS
    .int CHECKSUM



/*
 * GDT (Global Descriptor Table) data needed to enter in protected mode. At
 * the moment it contains data and code segments for ring 0.
 * 
 * CODE_PL0_SEL and DATA_PL0_SEL are used to fill the segment registers after
 * GDT was loaded. They are offsets from the beginning of GDT.
 *
 */

.data
    .align 4

    /* GDT pointer. */

    gdt_ptr:
        .short gdt_end - gdt_null - 1
        .int gdt_null

    /* GDT */


    gdt_null:
        .int 0
        .int 0

    gdt_code_pl0:
        .quad GDT_ENTRY(0, 0x000FFFFF, (GDT_CODE_PL0))

    gdt_data_pl0:
        .quad GDT_ENTRY(0, 0x000FFFFF, (GDT_DATA_PL0))

    gdt_end:

.set CODE_PL0_SEL, gdt_code_pl0 - gdt_null
.set DATA_PL0_SEL, gdt_data_pl0 - gdt_null



/* Create a kstack so that the entry point in the kernel can be called. */

.set KSTACK_SIZE, 4096

.bss
    .align 16

    kstack: .skip KSTACK_SIZE
    ljmp_addr: .skip 0x06



/* Set up GDT and the stack, after that kmain can be called. */

.text

_start:

disable_intrpt:

    cli

prot_to_real:

    /* Switch to real mode to be able to execute lgdt. */

    mov %cr0, %eax
    and $~0x01, %eax
    mov %eax, %cr0

enable_a20:

    /*
     * Read the value from I/O port FAST_A20_GATE, test to A20_ENABLED_BIT,
     * if the result is 0 then enable the A20 line and unset bit 0 because
     * we don't want to fast reset, else just skip this step.
     *
     * This is stil incomplete because the hardware may not support this kind
     * of enabling.
     *
     */

    in $FAST_A20_GATE, %al
    test $A20_ENABLED_BIT, %al
    jnz .skip_a20

    or $A20_ENABLED_BIT, %al
    and $~FAST_RESET_MASK, %al

    out %al, $FAST_A20_GATE

.skip_a20:


gdt_init:

    /*
     * Zero ds register because we want to work with the physical address of
     * gdt_ptr rather than with its linear address. Load the gdt_ptr and enter
     * in protected mode to make the far jump and change the cs register.
     *
     */

    xor %ax, %ax
    mov %ax, %ds

    lgdt gdt_ptr

    mov %cr0, %eax
    or $0x01, %eax
    mov %eax, %cr0

    jmp $CODE_PL0_SEL, $gdt_flush

gdt_flush:

    /*
     * At this moment, cs has the value CODE_PL0_VALUE, we need to set the rest
     * of segment register. They will all have the same value,
     * namely DATA_PL0_SEL.
     *
     */

    mov $DATA_PL0_SEL, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

enable_intrpt:

    sti

stack_init:

    /* Set the stack pointer to the top of the stack declared in bss. */

    mov $kstack, %esp
    add $KSTACK_SIZE, %esp

kentry:

    /*
     * Now that we are in protected mode and the stack is set up we cann call
     * the kernel entry point.
     *
     */

    call kmain
    cli

.halt:
    jmp .halt

