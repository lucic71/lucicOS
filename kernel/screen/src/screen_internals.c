#include "screen_internals.h"
#include "cursor.h"

#include "lib/vga.h"

#include <stddef.h>
#include <stdint.h>

/*
 * _screen_putchar_at:
 * ------------------
 *
 *  Put the character @c of color @color in framebuffer at the index determined
 *  by @x and @y coordinates.
 *
 */

void _screen_putchar_at(char c, uint16_t color, size_t x, size_t y) {

    const size_t index = y * VGA_WIDTH + x;
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
        fbuffer[(VGA_HEIGHT - 1) * VGA_WIDTH + 1] = vga_entry(' ', screen_color);

}

/*
 * _screen_putchar:
 * --------------
 *
 *  Wrapper function over _screen_putchar_at. Puts the character in framebuffer and
 *  has support for newline characters.
 *
 *  Side efects:
 *   scrolls up the screen whenever there is no more space
 *   moves the cursor after each displayed characte
 *
 */

void _screen_putchar(char c) {

    if (screen_column == VGA_WIDTH || c == '\n') {
        
        screen_column = 0;

        if (screen_row == VGA_HEIGHT - 1)
            _screen_scroll_up();
        else
            screen_row++;

    }

    if (c == '\n')
        return;

    _screen_putchar_at(c, screen_color, screen_column++, screen_row);
    _screen_move_cursor(screen_column, screen_row);

}
