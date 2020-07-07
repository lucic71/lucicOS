#include "i386/gdt.h"
#include "i386/a20.h"

.global gdt_init
.extern gdt_return

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


.text

gdt_init:

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


gdt_load:

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

    jmp gdt_return
