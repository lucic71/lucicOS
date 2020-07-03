#include "i386/idt.h"

/* Data structures used to fill the IDT. */

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

/* Routine that installs the IDT. */

extern void idt_flush(uint32_t idt_ptr);

/*
 * idt_init:
 * ---------
 *
 *  After the table and the table pointer are filled, flush the table pointer
 *  using gdt_flush.
 *
 */

void idt_init(void) {

    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t) &idt_entries;

    for (int i = 0; i < 256; i++)
        idt_entries[i] = (idt_entry_t) {};

    idt_flush((uint32_t) &idt_ptr);

}

