.extern isr_handler

/* Macros that define the entry point in ISRs with and without an error code. */

.macro ISR_NO_ERRCODE _isr_nr
.global isr\_isr_nr
isr\_isr_nr:
    cli
    push $0x00
    push $\_isr_nr
    jmp isr_common_stub
.endm

.macro ISR_ERRCODE _isr_nr
.global isr\_isr_nr
isr\_isr_nr:
    cli
    push $\_isr_nr
    jmp isr_common_stub
.endm

/* Expandation of the above mentioned macros. */

ISR_NO_ERRCODE 0
ISR_NO_ERRCODE 1
ISR_NO_ERRCODE 2
ISR_NO_ERRCODE 3
ISR_NO_ERRCODE 4
ISR_NO_ERRCODE 5
ISR_NO_ERRCODE 6
ISR_NO_ERRCODE 7
ISR_ERRCODE 8
ISR_NO_ERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NO_ERRCODE 15
ISR_NO_ERRCODE 16
ISR_NO_ERRCODE 17
ISR_NO_ERRCODE 18
ISR_NO_ERRCODE 19
ISR_NO_ERRCODE 20
ISR_NO_ERRCODE 21
ISR_NO_ERRCODE 22
ISR_NO_ERRCODE 23
ISR_NO_ERRCODE 24
ISR_NO_ERRCODE 25
ISR_NO_ERRCODE 26
ISR_NO_ERRCODE 27
ISR_NO_ERRCODE 28
ISR_NO_ERRCODE 29
ISR_NO_ERRCODE 30
ISR_NO_ERRCODE 31

/*
 * Stub for ISRs. It must push the context on the stack and change the PL.
 * After the isr_handler was called the context will be restored and the
 * error code and the request number will be cleared from the stack.
 *
 */

isr_common_stub:

    pusha

    mov %ds, %ax
    push %eax

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call isr_handler

    pop %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa
    add $0x08, %esp

    sti
    iret
