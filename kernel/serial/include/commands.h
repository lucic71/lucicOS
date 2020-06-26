#ifndef SERIAL_COMMANDS_H_
#define SERIAL_COMMANDS_H_

/*
 * SERIAL_LINE_ENABLE_DLAB: (Divisor Latch Access Bit)
 *  When put in line command port, this byte tells the serial to expect the
 *  least significant byte of the divisor value in data port and the most
 *  significant byte in interrupt enable port.
 *
 *  A description of the bits in line command port can be found in the
 *  documentation of this module.
 *  
 */

#define SERIAL_LINE_ENABLE_DLAB 0x80

/*
 * SERIAL_DATA_LINE_CONFIG:
 *  Disable break control, set no parity, one stop bit and 8 bits for data.
 *
 */

#define SERIAL_DATA_LINE_CONFIG 0x03

/*
 * SERIAL_FIFO_BUFFER_CONFIG:
 *  
 *  0xC7 = 0b11000111
 *
 *  Set the trigger threshold value to 14 bytes in 16 bytes mode (bits 7 ans 6).
 *  Set 16 byte mode (bit 5)
 *  Disable Direct Memory Access (bit 3)
 *  Clear transmit FIFO (bit 2)
 *  Clear receive FIFO (bit 1)
 *  Enable FIFO (bit 0)
 *
 */

#define SERIAL_FIFO_BUFFER_CONFIG 0xC7

/*
 * SERIAL_MODEM_CONFIG:
 *  Activate RTS (Ready To Transmit) and DTR (Data Terminal Ready) to be triggered
 *  when necessary.
 *
 */

#define SERIAL_MODEM_CONFIG 0x03

/*
 * LINE_STATUS_FIFO_EMPTY:
 *  When tested against the value read from line status port, this value tells
 *  whether the FIFO is empty or not.
 *
 */

#define LINE_STATUS_FIFO_EMPTY 0x20

#endif
