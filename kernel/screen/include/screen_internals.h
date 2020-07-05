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
 *  @param c          - Char to be displayed
 *  @param color      - Color attributes of @c
 *  @param column     - Vertical position
 *  @param row        - Horizontal position
 *
 */

void _screen_putchar_at(char c, uint16_t color, size_t column, size_t row);
void _screen_putchar(char c);

/*
 * _screen_scroll_up:
 *  Deletes the last line of framebuffer and moves other lines up by one.
 *
 */

void _screen_scroll_up(void);

/*
 * _screen_delete_at:
 *  Deletes a character at a given position.
 *
 * @param column - Vertical position
 * @param row    - Horizontal position
 *
 */

void _screen_delete_at(size_t column, size_t row);

/*
 * _find_last_nonwhite_column:
 *
 *
 * @return - the column with the last nonwhite character on the previous
 * line.
 */

size_t _find_last_nonwhite_column(void);

/*
 * _is_whitespace:
 *  
 * @param column - Vertical position
 * @param row    - Horizontal poistion
 * @return       - 1 if it is whitespace
 *                 0 else
 *  
 */

int _is_whitespace(size_t column, size_t row);

#endif
