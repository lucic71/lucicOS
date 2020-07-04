#include "kernel/screen.h"

#include "framebuffer.h"
#include "screen_internals.h"

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

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {

            const size_t index = y * VGA_WIDTH + x;
            fbuffer[index] = vga_entry(' ', screen_color);

        }
    }

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

