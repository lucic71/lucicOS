#ifndef INTRPT_H_
#define INTRPT_H_

/*
 * idt_init:
 *  Creates an array of 256 empty entries that will be loaded in the CPU as
 *  an IDT.
 *
 */

void idt_init(void);

#endif
