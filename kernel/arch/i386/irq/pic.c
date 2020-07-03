#include "i386/pic.h"
#include "i386/irq.h"

#include <stdio.h>

/*
 * pic_remap:
 * ----------
 *
 *  Save the state of the data ports. Initialize the PICs, write the vector
 *  offsets, tell the master PIC about the slave and inform the slave about
 *  its identity; and set the PICs in 8086 mode.
 *  
 */

void pic_remap(uint8_t offset1, uint8_t offset2) {

    uint8_t d1, d2;

    d1 = inb(PIC1_DATA);
    d2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);

    outb(PIC1_DATA, ICW3_SLAVE_IRQ);
    outb(PIC2_DATA, ICW3_SLAVE_ID);

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, d1);
    outb(PIC2_DATA, d2);

}

/*
 * pic_send_eoi:
 * -------------
 *
 *
 */

void pic_send_eoi(uint8_t irq) {

    if (irq >= IRQ8)
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);

}
