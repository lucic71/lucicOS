#ifndef SERIAL_H_
#define SERIAL_H_

#include "stdint.h"

/* Serial ports I/O addresses. */

#define COM1 0X3F8
#define COM2 0X2F8
#define COM3 0X3E8
#define COM4 0X2E8

/*
 * serial_init:
 *  Configure the serial to transmit data. The configuration will affect the
 *  baud rate, the data line, the FIFO buffer and the modem. For more info
 *  see serial module Documentation.
 *
 * @param com - The serial port
 *
 */

void serial_init(uint16_t com);

/*
 * serial_write:
 *  Writes a buffer to the serial port.
 *
 * @param com  - The serial port
 * @param data - The buffer to be written
 * @param len  - Length of the buffer
 * @return     - The characters successfully written
 *
 */

int serial_write(uint16_t com, char *data, int len);

#endif
