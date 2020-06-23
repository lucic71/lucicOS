#ifndef CURSOR_H_
#define CURSOR_H_

#include "stdint.h"

/* Cursor I/O ports. */

#define C_COMMAND_PORT 0x3D4
#define C_DATA_PORT    0x3D5

/* Cursor I/O port commands. */

#define C_HIGH_BYTE_COMMAND 0X0E
#define C_LOW_BYTE_COMMAND  0x0F

/*
 * smove_cursor:
 *  Moves the cursor of the framebuffer to a give position calculated using
 *  @x and @y coordinates.
 *
 * @param x - horizontal position
 * @param y - vertical position
 *
 */

void smove_cursor(uint8_t x, uint8_t y);

#endif
