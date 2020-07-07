#include "i386/isr.h"

#include "i386/idt.h"
#include "i386/context.h"

#include "kernel/serial.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Extern symbol defined in idt.c */

extern idt_entry_t idt_entries[256];

/* External Interrupt Service Routines. */

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/*
 * isr_init:
 * ---------
 *  
 *  Fill the first 32 entries in IDT.
 *
 */

void isr_init(void) {

    idt_entries[0] = idt_set_gate((uint32_t) isr0, 0x08, 0x8E);
    idt_entries[1] = idt_set_gate((uint32_t) isr1, 0x08, 0x8E);
    idt_entries[2] = idt_set_gate((uint32_t) isr2, 0x08, 0x8E);
    idt_entries[3] = idt_set_gate((uint32_t) isr3, 0x08, 0x8E);
    idt_entries[4] = idt_set_gate((uint32_t) isr4, 0x08, 0x8E);
    idt_entries[5] = idt_set_gate((uint32_t) isr5, 0x08, 0x8E);
    idt_entries[6] = idt_set_gate((uint32_t) isr6, 0x08, 0x8E);
    idt_entries[7] = idt_set_gate((uint32_t) isr7, 0x08, 0x8E);
    idt_entries[8] = idt_set_gate((uint32_t) isr8, 0x08, 0x8E);
    idt_entries[9] = idt_set_gate((uint32_t) isr9, 0x08, 0x8E);
    idt_entries[10] = idt_set_gate( (uint32_t) isr10, 0x08, 0x8E);
    idt_entries[11] = idt_set_gate( (uint32_t) isr11, 0x08, 0x8E);
    idt_entries[12] = idt_set_gate( (uint32_t) isr12, 0x08, 0x8E);
    idt_entries[13] = idt_set_gate( (uint32_t) isr13, 0x08, 0x8E);
    idt_entries[14] = idt_set_gate( (uint32_t) isr14, 0x08, 0x8E);
    idt_entries[15] = idt_set_gate( (uint32_t) isr15, 0x08, 0x8E);
    idt_entries[16] = idt_set_gate( (uint32_t) isr16, 0x08, 0x8E);
    idt_entries[17] = idt_set_gate( (uint32_t) isr17, 0x08, 0x8E);
    idt_entries[18] = idt_set_gate( (uint32_t) isr18, 0x08, 0x8E);
    idt_entries[19] = idt_set_gate( (uint32_t) isr19, 0x08, 0x8E);
    idt_entries[20] = idt_set_gate( (uint32_t) isr20, 0x08, 0x8E);
    idt_entries[21] = idt_set_gate( (uint32_t) isr21, 0x08, 0x8E);
    idt_entries[22] = idt_set_gate( (uint32_t) isr22, 0x08, 0x8E);
    idt_entries[23] = idt_set_gate( (uint32_t) isr23, 0x08, 0x8E);
    idt_entries[24] = idt_set_gate( (uint32_t) isr24, 0x08, 0x8E);
    idt_entries[25] = idt_set_gate( (uint32_t) isr25, 0x08, 0x8E);
    idt_entries[26] = idt_set_gate( (uint32_t) isr26, 0x08, 0x8E);
    idt_entries[27] = idt_set_gate( (uint32_t) isr27, 0x08, 0x8E);
    idt_entries[28] = idt_set_gate( (uint32_t) isr28, 0x08, 0x8E);
    idt_entries[29] = idt_set_gate( (uint32_t) isr29, 0x08, 0x8E);
    idt_entries[30] = idt_set_gate( (uint32_t) isr30, 0x08, 0x8E);
    idt_entries[31] = idt_set_gate( (uint32_t) isr31, 0x08, 0x8E);

}

/* Exception messages for unhandled faults. */

char *exception_messages[] = {
	"Division by zero",				
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",			
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",						
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",		
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

/* isr_handler:
 *  Handles an incomming request by calling the appropiate handler or printing
 *  an exception message.
 *
 *  @param context - the context of the caller
 *
 */

void isr_handler(context_t context) {

    serial_write(COM1, "Unhandled exception: ", strlen("Unhandled exception: "));
    serial_write(COM1, exception_messages[context.int_no], strlen(exception_messages[context.int_no]));
    serial_write(COM1, "\n", 1);

}

