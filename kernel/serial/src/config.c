#include "config.h"
#include "ports.h"
#include "commands.h"

#include "lib/memio.h"

/*
 * serial_config_baud_rate:
 * ------------------------
 *
 *  Check if divisor is valid, if so enable DLAB and write the high and low
 *  byte in interrupt enable and data port.
 *
 */

void serial_config_baud_rate(uint16_t com, uint16_t divisor) {

    if (!divisor)
        return;

    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

    outb(SERIAL_INTRPT_ENABLE_PORT(com), (divisor >> 8) & 0X00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);

}

/*
 * serial_config_data_line:
 * ------------------------
 *
 * Configure data line accordingly to the command defined in commands.h.
 *
 */

void serial_config_data_line(uint16_t com) {

    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_DATA_LINE_CONFIG);

}

/*
 * serial_config_fifo_buffer:
 * --------------------------
 *
 * Configure fifo buffer accordingly to the command defined in commands.h.
 *
 */

void serial_config_fifo_buffer(uint16_t com) {

    outb(SERIAL_FIFO_COMMAND_PORT(com), SERIAL_FIFO_BUFFER_CONFIG);

}

/*
 * serial_config_modem:
 * --------------------
 *
 * Configure the modem accordingly to the command defined in commands.h.
 *
 */

void serial_config_modem(uint16_t com) {

    outb(SERIAL_MODEM_COMMAND_PORT(com), SERIAL_MODEM_CONFIG);

}
