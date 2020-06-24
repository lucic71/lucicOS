#ifndef IO_H_
#define IO_H_

#include "stdint.h"

/*
 * outb:
 *  Writes the second parameter to a I/O port specified in the first parameter.
 *
 * @param port - I/O port where data is written
 * @param data - data to be written to the port
 *
 */

void outb(uint16_t port, uint8_t data);

/*
 * inb:
 *  Reads a byte from an I/O port.
 *
 * @param port - The address of the I/O port.
 * @return     - The read byte
 *
 */

uint8_t inb(uint16_t port);

#endif
