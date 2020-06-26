#ifndef SERIAL_STATUS_H_
#define SERIAL_STATUS_H_

#include "stdint.h"

/*
 * serial_is_transmit_fifo_empty:
 *  Checks if the transmit FIFO is empty.
 *
 * @param com - The serial to test
 * @return    - 0 if the transmit FIFO is not empty
 *              1 if the transmit FIFO is empty
 *
 */

int serial_is_transmit_fifo_empty(uint16_t com);

#endif
