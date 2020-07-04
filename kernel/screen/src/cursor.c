#include "cursor.h"

#include "lib/memio.h"
#include "lib/vga.h"

/*
 * _screen_move_cursor:
 * -------------------
 *
 *  Compute the screen index, @sindex, using the given coordinates and send
 *  its high and low bytes to cursor data port.
 *
 *  However before transmitting data, the hardware must be informed about
 *  which byte it will receive. This is done by sending a specific signal to
 *  cursor command port.
 *
 */

void _screen_move_cursor(uint8_t x, uint8_t y) {

    uint16_t sindex = y * VGA_WIDTH + x;

    outb(CURSOR_COMMAND_PORT, CURSOR_HIGH_BYTE_COMMAND);
    outb(CURSOR_DATA_PORT, ((sindex >> 8)) & 0x00FF);

    outb(CURSOR_COMMAND_PORT, CURSOR_LOW_BYTE_COMMAND);
    outb(CURSOR_DATA_PORT, sindex & 0x00FF);

}
