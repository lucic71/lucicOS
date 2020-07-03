#ifndef PIC_H_
#define PIC_H_

#include <stdint.h>

#include "lib/memio.h"

/* Master and slave PIC I/O ports. */

#define PIC1 0x20
#define PIC2 0xA0

/* Command and data port for each PIC. */

#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2 + 1)

/* PIC Initialization Command Words. */

#define ICW1_ICW4      0x01
#define ICW1_SINGLE    0X02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL     0X08
#define ICW1_INIT      0X10

#define ICW3_SLAVE_IRQ 0x04
#define ICW3_SLAVE_ID  0X02

#define ICW4_8086       0x01
#define ICW4_AUTO       0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM       0x10

/* End of Interrupt. */

#define PIC_EOI 0X20

/*
 * pic_remap:
 *  Initializes and remaps the master and slave PICs.
 *
 *  @param offset1 - offset for master PIC in IDT
 *  @param offset2 - offset for slave PIC in IDT
 *
 */

void pic_remap(uint8_t offset1, uint8_t offset2);

/*
 * pic_send_eoi:
 *  Sends EOI signal to PICs.
 *
 * @param irq - IRQ number
 *
 */

void pic_send_eoi(uint8_t irq);

#endif
