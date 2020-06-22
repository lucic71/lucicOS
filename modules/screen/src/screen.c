#include "screen.h"
#include "vga.h"

/*
 * Variables that determine the state of the screen.
 *
 */

static unsigned short *fbuffer;

static unsigned screen_row;
static unsigned screen_column;
static unsigned screen_color;

/*
 * Private functions used to implement the public ones.
 *
 */

void sputchar_at(char c, unsigned short color, unsigned x, unsigned y);
void sputchar(char c);

void sscroll_up(void);

/*
 * sinit:
 * ------
 *
 *  Initialize @screen_row and @screen_column.
 *  Set the @screen color (at the moment the screen has preset colors).
 *  Initialize the framebuffer address and its conent.
 *
 */

void sinit(void) {

    screen_row = 0;
    screen_column = 0;
    screen_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);

    fbuffer = (unsigned short *) FBUFFER_START_ADDR;

    for (unsigned y = 0; y < VGA_HEIGHT; y++) {
        for (unsigned x = 0; x < VGA_WIDTH; x++) {

            const unsigned index = y * VGA_WIDTH + x;
            fbuffer[index] = vga_entry(' ', screen_color);

        }
    }

}

/*
 * swrite:
 * -------
 *
 *  Writes the characters one by one in framebuffer using a specialized function.
 *
 */
    
int swrite(char *buf, unsigned int len) {

    volatile unsigned i = 0;

    for (i = 0; i < len; i++)
        sputchar(buf[i]);

    return i;
}

/*
 * PRIVATE FUNCTIONS
 *
 */

/*
 * sputchar_at:
 * ------------
 *
 *  Put the character @c of color @color in framebuffer at the index determined
 *  by @x and @y coordinates.
 *
 */

void sputchar_at(char c, unsigned short color, unsigned x, unsigned y) {

    const unsigned index = y * VGA_WIDTH + x;
    fbuffer[index] = vga_entry(c, color);

}

/*
 * sscroll_up:
 * -----------
 *
 *  Scroll the first 24 lines and delete the content of the last line.
 *
 */

void sscroll_up(void) {

    unsigned i;
    
    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT - 80; i++)
        fbuffer[i] = fbuffer[i + 80];

    for (i = 0; i < VGA_WIDTH; i++)
        fbuffer[(VGA_HEIGHT - 1) * VGA_WIDTH + 1] = vga_entry(' ', screen_color);

}

/*
 * tpuchar:
 * --------
 *
 *  Wrapper function over sputchar_at. Puts the character in framebuffer and
 *  furthermore supports newline characters and scrolling the screen up.
 *
 */

void sputchar(char c) {

    if (screen_column == VGA_WIDTH || c == '\n') {
        
        screen_column = 0;

        if (screen_row == VGA_HEIGHT - 1)
            sscroll_up();
        else
            screen_row++;

    }

    if (c == '\n')
        return;

    sputchar_at(c, screen_color, screen_column++, screen_row);

}

