#ifndef IRQ_H_
#define IRQ_H_

#include "context.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

/*
 * irq_init:
 *  Initializes the PIC and puts pointers to IRQ gates in IDT.
 *
 */

void irq_init(void);

/* Function typedef for IRQ handlers. */

typedef void (*irq_t)(context_t);

/*
 * register_irq:
 *  Creates a handler for an IRQ with IRQ number irq_no.
 *
 *  @param irq_no - IRQ number
 *
 */

void register_irq(uint8_t irq_no, irq_t handler);

#endif
