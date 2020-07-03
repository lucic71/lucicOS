.extern irq_handler

/* Macro that defines an IRQ gate using the irq number and its corresponding IDT index. */

.macro IRQ _irq_nr, _idt_nr
.global irq\_irq_nr
irq\_irq_nr:
    cli
    push $0x00
    push $\_idt_nr
    jmp irq_common_stub
.endm

/* Define the gates. */

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

/*
 * Common stub that saves the context on the stack and restores it after
 * the handler is done 
 * 
 * To see a more comprehensibile layout of the data saved on the stack, please
 * check context.h
 *
 */

irq_common_stub:

    pusha

    mov %ds, %ax
    push %eax

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call irq_handler

    pop %ebx
    mov %bx, %ds
    mov %bx, %es
    mov %bx, %fs
    mov %bx, %gs

    popa
    add $0x08, %esp
    sti
    iret
