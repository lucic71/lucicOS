#ifndef TABLES_ISR_H_
#define TABLES_ISR_H_

/*
 * isr_init:
 *  Fills the first 32 entries in IDT after it was loaded with the predefined
 *  faults and interrupts.
 *
 */

void isr_init(void);

#endif
