#ifndef SERIAL_CONFIG_H_
#define SERIAL_CONFIG_H_

#include "stdint.h"

/*
 * serial_config_baud_rate:
 *  Sets the speed of the data being sent. The default speed is 115200 bits/s.
 *  The resulting speed will be equal to 115200/divisor bits/s after this
 *  routine ends.
 *
 *  If divisor is 0 the routine does nothing and the baud rate will have the
 *  default value (115200 bits/s).
 *
 *  @param com     - The serial to configure
 *  @param divisor - The divisor
 *
 */

void serial_config_baud_rate(uint16_t com, uint16_t divisor);

/*
 * serial_config_data_line:
 *  Sets the protocol for transmitting the data. The default is 8N1 (8 bits of
 *  data, no parity, one stop bit). Break control is disabled.
 *
 *  @param com - The serial to configure
 *
 */

void serial_config_data_line(uint16_t com);

/*
 * serial_config_fifo_buffer:
 *  Sets the configuration of the buffer. This includes the size of the buffer,
 *  access mode and other settings.
 *
 *  @param com - The serial to configure
 *
 */

void serial_config_fifo_buffer(uint16_t com);

/*
 * serial_config_modem:
 *  Configures the modem. Currently because the serial is not configured to
 *  receive data, interrupts won't be enabled.
 *
 *  @param com - The serial to configure
 *
 */

void serial_config_modem(uint16_t com);

#endif
