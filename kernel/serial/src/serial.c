#include "kernel/serial.h"

#include "config.h"
#include "status.h"
#include "ports.h"

#include "lib/memio.h"

/* Private functions declaration. */

static void serial_putchar(uint16_t com, char c);

/*
 * serial_init:
 * ------------
 *
 *  Configure the baud rate, data line, FIFO buffer and the modem. Because
 *  there is no special requirement about the baud rate, 0 will be passed
 *  as divisor (This has no effect on the baud rate).
 *
 */

void serial_init(uint16_t com) {

    serial_config_baud_rate(com, 0x00);

    serial_config_data_line(com);
    serial_config_fifo_buffer(com);
    serial_config_modem(com);

}


/*
 * serial_write:
 * -------------
 *
 *  Put each character in the buffer on the serial port.
 *
 */

int serial_write(uint16_t com, char *data, int len) {

    volatile int i = 0;

    for (i = 0; i < len; i++)
        serial_putchar(com, data[i]);

    return i;

}

/* PRIVATE FUNCTIONS. */

/*
 * serial_putchar:
 * ---------------
 *
 *  Wait for the FIFO buffer to be empty, then write the character on the data
 *  port.
 *
 */

static void serial_putchar(uint16_t com, char c) {

    while (!serial_is_transmit_fifo_empty(com));

    outb(SERIAL_DATA_PORT(com), c);

}
