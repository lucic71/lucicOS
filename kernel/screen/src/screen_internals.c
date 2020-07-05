#include "screen_internals.h"
#include "cursor.h"

#include "lib/vga.h"

#include <stddef.h>
#include <stdint.h>

/*
 * _screen_delete_at:
 * ------------------
 *
 *  Replaces the character at (row, column) with a whitespace.
 *
 */

void _screen_delete_at(size_t column, size_t row) {

    const size_t index = row * VGA_WIDTH + column;
    fbuffer[index] = vga_entry(' ', screen_color);

}

/*
 * _screen_putchar_at:
 * ------------------
 *
 *  Put the character @c of color @color in framebuffer at the index determined
 *  by @x and @y coordinates.
 *
 */

void _screen_putchar_at(char c, uint16_t color, size_t column, size_t row) {

    const size_t index = row * VGA_WIDTH + column;
    fbuffer[index] = vga_entry(c, color);

}

/*
 * _screen_scroll_up:
 * -----------------
 *
 *  Scroll the first 24 lines and delete the content of the last line.
 *
 */

void _screen_scroll_up(void) {

    size_t i;
    
    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT - 80; i++)
        fbuffer[i] = fbuffer[i + 80];

    for (i = 0; i < VGA_WIDTH; i++)
        _screen_delete_at(i, VGA_HEIGHT - 1);

}

/*
 * _screen_putchar:
 * --------------
 *
 *  Wrapper function over _screen_putchar_at. Puts the character in framebuffer and
 *  has support for newline characters.
 *
 *  If the routine writes to the last position of a line then the cursor will be
 *  moved on the first position of the following line. If the routine writes to
 *  the last column of the last line the screen will be scrolled and the cursor
 *  will be put on the next free line.
 *
 *  Side efects:
 *   scrolls up the screen whenever there is no more space
 *   moves the cursor after each displayed characte
 *
 */

void _screen_putchar(char c) {

    if (screen_column == VGA_WIDTH - 1 && screen_row == VGA_HEIGHT - 1) {

        _screen_putchar_at(c, screen_color, screen_column, screen_row);
        _screen_scroll_up();

        screen_column = 0;
        _screen_move_cursor(screen_column, screen_row);

        return;

    }

    if (screen_column == VGA_WIDTH || c == '\n') {
        
        screen_column = 0;

        if (screen_row == VGA_HEIGHT - 1)
            _screen_scroll_up();
        else
            screen_row++;

    }

    if (c == '\n') {

        _screen_move_cursor(screen_column, screen_row);
        return;

    }

    _screen_putchar_at(c, screen_color, screen_column, screen_row);
    screen_column++;
    _screen_move_cursor(screen_column, screen_row);

}

/*
 * _is_whitespace:
 * ---------------
 *
 */

int _is_whitespace(size_t column, size_t row) {

    int index = row * VGA_WIDTH + column;
    return fbuffer[index] == vga_entry(' ', screen_color);

}

/*
 * _find_last_nonwhite_column:
 * ---------------------------
 *
 *  Goes on the last line and returns the first column that has a nonwhite
 *  char. The traversal is from the end of the line to the beginning.
 *  It will return 0 if there is no nonwhite character.
 *
 */

size_t _find_last_nonwhite_column(void) {

    int row = screen_row - 1;
    int y = VGA_WIDTH;

    for (; y > 0; y--)
        if (!_is_whitespace(y, row))
            break;

    return y;

}
