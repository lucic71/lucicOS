#include "i386/irq.h"
#include "i386/pic.h"

#include "i386/idt.h"
#include "i386/context.h"

#include "kernel/serial.h"

#include <stdio.h>
#include <string.h>

/* Extern symbol defined in idt.c */

extern idt_entry_t idt_entries[256];

/* External Interrupt Service Routines. */

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/*
 * irq_init:
 * ---------
 *
 *  Remap PIC pins to match the IRQ starting from 32.
 *
 */

void irq_init(void) {

    pic_remap(IRQ0, IRQ8);

    idt_entries[32] = idt_set_gate( (uint32_t) irq0, 0x08, 0x8E);
    idt_entries[33] = idt_set_gate( (uint32_t) irq1, 0x08, 0x8E);
    idt_entries[34] = idt_set_gate( (uint32_t) irq2, 0x08, 0x8E);
    idt_entries[35] = idt_set_gate( (uint32_t) irq3, 0x08, 0x8E);
    idt_entries[36] = idt_set_gate( (uint32_t) irq4, 0x08, 0x8E);
    idt_entries[37] = idt_set_gate( (uint32_t) irq5, 0x08, 0x8E);
    idt_entries[38] = idt_set_gate( (uint32_t) irq6, 0x08, 0x8E);
    idt_entries[39] = idt_set_gate( (uint32_t) irq7, 0x08, 0x8E);
    idt_entries[40] = idt_set_gate( (uint32_t) irq8, 0x08, 0x8E);
    idt_entries[41] = idt_set_gate( (uint32_t) irq9, 0x08, 0x8E);
    idt_entries[42] = idt_set_gate( (uint32_t) irq10, 0x08, 0x8E);
    idt_entries[43] = idt_set_gate( (uint32_t) irq11, 0x08, 0x8E);
    idt_entries[44] = idt_set_gate( (uint32_t) irq12, 0x08, 0x8E);
    idt_entries[45] = idt_set_gate( (uint32_t) irq13, 0x08, 0x8E);
    idt_entries[46] = idt_set_gate( (uint32_t) irq14, 0x08, 0x8E);
    idt_entries[47] = idt_set_gate( (uint32_t) irq15, 0x08, 0x8E);

}

/*
 * register_irq:
 * -------------
 *
 *  Register a handler in intrpt_handlers array.
 *
 */

irq_t intrpt_handlers[256];

void register_irq(uint8_t irq_no, irq_t handler) {

    intrpt_handlers[irq_no] = handler;

}

/*
 * irq_handler:
 * ------------
 *
 *  Using the intrpt number present in context, choose the appropiate handler.
 *  The routine should also send and EOI signal to PIC.
 *
 */

void irq_handler(context_t context) {

    pic_send_eoi(context.int_no);

    irq_t handler = intrpt_handlers[context.int_no];
    if (handler)
        handler(context);

    else {

        char unhandled_intrpt[] = "Unhandled interrupt request\n";
        serial_write(COM1, unhandled_intrpt, strlen(unhandled_intrpt));

    }


}
