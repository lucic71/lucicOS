#include "kernel/screen.h"

#include "framebuffer.h"
#include "screen_internals.h"
#include "cursor.h"

#include "lib/vga.h"

#include <stddef.h>

/*
 * screen_init:
 * ------------
 *
 *  Initialize @screen_row and @screen_column.
 *  Set the @screen color (at the moment the screen has preset colors).
 *  Initialize the framebuffer address and its conent.
 *
 */

void screen_init(void) {

    screen_row = 0;
    screen_column = 0;
    screen_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);

    fbuffer = (uint16_t *) FBUFFER_START_ADDR;

    for (size_t row = 0; row < VGA_HEIGHT; row++)
        for (size_t column = 0; column < VGA_WIDTH; column++) 
            _screen_delete_at(column, row);

}

/*
 * screen_write:
 * -------------
 *
 *  Writes the characters one by one in framebuffer using a specialized function.
 *
 */
    
size_t screen_write(char *buf, size_t len) {

    volatile size_t i = 0;

    for (i = 0; i < len; i++)
        _screen_putchar(buf[i]);

    return i;
}

/*
 * screen_delete:
 * --------------
 *
 *  Deletes the current character and updates the cursor. If current position
 *  is (0, 0) then do nothing. If current position is at the beginning of a
 *  line then find the last nonwhite element on the last line and move the
 *  cursor there. Else just delete the current element.
 *
 *  Side effects:
 *   cursor position will be affected too.
 *
 */

void screen_delete(void) {

    if (!screen_column && !screen_row)
        return;

    if (!screen_column && screen_row) {

        screen_column = _find_last_nonwhite_column();
        screen_row--;

    } else
        screen_column--;

    _screen_delete_at(screen_column, screen_row);
    _screen_move_cursor(screen_column, screen_row);

}

