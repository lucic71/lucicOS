#ifndef SCREEN_INTERNALS_H_
#define SCREEN_INTERNALS_H_

#include <stdint.h>
#include <stddef.h>

/* State of the screen. */

uint16_t *fbuffer;

size_t screen_row;
size_t screen_column;
size_t screen_color;

/*
 * _screen_putchar_*:
 *  Put character at a specified position or put character at the next position
 *  available in framebuffer acording to state variables.
 *
 *  @param c     - Char to be displayed
 *  @param color - Color attributes of @c
 *  @param x     - Vertical position
 *  @param y     - Horizontal position
 *
 */

void _screen_putchar_at(char c, uint16_t color, size_t x, size_t y);
void _screen_putchar(char c);

/*
 * _screen_scroll_up:
 *  Deletes the last line of framebuffer and moves other lines up by one.
 *
 */

void _screen_scroll_up(void);

#endif
