#include "cursor.h"

#include "memio.h"
#include "vga.h"

/*
 * smove_cursor:
 * -------------
 *
 *  Compute the screen index, @sindex, using the given coordinates and send
 *  its high and low bytes to cursor data port.
 *
 *  However before transmitting data, the hardware must be informed about
 *  which byte it will receive. This is done by sending a specific signal to
 *  cursor command port.
 *
 */

void smove_cursor(uint8_t x, uint8_t y) {

    uint16_t sindex = y * VGA_WIDTH + x;

    outb(C_COMMAND_PORT, C_HIGH_BYTE_COMMAND);
    outb(C_DATA_PORT, ((sindex >> 8)) & 0x00FF);

    outb(C_COMMAND_PORT, C_LOW_BYTE_COMMAND);
    outb(C_DATA_PORT, sindex & 0x00FF);

}
