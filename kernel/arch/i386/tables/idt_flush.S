.global idt_flush

/*
 * idt_flush - load the 48bit memory that contains the information about
 * the IDT in its corresponding register using the LIDT instruction.
 *
 * @param [esp + 4] - pointer to a 48bit memory location
 *
 */

idt_flush:

    mov 0x04(%esp), %eax
    lidt (%eax)
    ret
