.global outb
.global inb

/*
 * outb:
 * -----
 *
 *  Passes the port number in %dx and the value to be written in %al. Using
 *  the outb instruction, the value is written in the I/O port.
 *
 */

outb:

    mov 0x04(%esp), %dx
    mov 0x08(%esp), %al

    outb %al, %dx
    ret

/*
 * inb:
 * ----
 *
 *  Passes the port number in %dx. It will return the value in that port after
 *  after calling the inb instruction.
 *
 */

inb:

    mov 0x04(%esp), %dx
    inb %dx, %al

    ret
