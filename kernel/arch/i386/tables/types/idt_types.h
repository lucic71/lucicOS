#ifndef INTRPT_IDT_H_
#define INTRPT_IDT_H_

#include "stdint.h"

/*
 * idt_entry_t  - entry in Interrupt Descriptor Table
 * idt_set_gate - creates an IDT entry
 *
 */

struct idt_entry_struct {

    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t base_high;

} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;


static inline idt_entry_t idt_set_gate(uint32_t base, uint16_t sel, uint8_t flags) {

    idt_entry_t entry;

    entry.base_low = base & 0xFFFF;
    entry.selector = sel;
    entry.zero = 0x00;
    entry.flags = flags;
    entry.base_high = (base >> 16) & 0xFFFF;

    return entry;
}

/* idt_ptr_t - IDT pointer that will be loaded in CPU */

struct idt_ptr_struct {

    uint16_t limit;
    uint32_t base;

} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

#endif
