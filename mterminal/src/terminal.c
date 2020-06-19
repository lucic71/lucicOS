#include "terminal.h"
#include "vga.h"

/*
 * Variables that determine the state of the terminal.
 *
 */

static unsigned short *fbuffer;

static unsigned terminal_row;
static unsigned terminal_column;
static unsigned terminal_color;

/*
 * Private functions used to implement the public ones.
 *
 */

void tputchar_at(char c, unsigned short color, unsigned x, unsigned y);
void tputchar(char c);

void tscroll_up(void);

/*
 * tinit:
 * ------
 *
 *  Initialize @terminal_row and @terminal_column.
 *  Set the @terminal color (at the moment the terminal has preset colors).
 *  Initialize the framebuffer address and its conent.
 *
 */

void tinit(void) {

    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);

    fbuffer = (unsigned short *) FBUFFER_START_ADDR;

    for (unsigned y = 0; y < VGA_HEIGHT; y++) {
        for (unsigned x = 0; x < VGA_WIDTH; x++) {

            const unsigned index = y * VGA_WIDTH + x;
            fbuffer[index] = vga_entry(' ', terminal_color);

        }
    }

}

/*
 * twrite:
 * -------
 *
 *  Writes the characters one by one in framebuffer using a specialized function.
 *
 */
    
int twrite(char *buf, unsigned int len) {

    volatile unsigned i = 0;

    for (i = 0; i < len; i++)
        tputchar(buf[i]);

    return i;
}

/*
 * PRIVATE FUNCTIONS
 *
 */

/*
 * tputchar_at:
 * ------------
 *
 *  Put the character @c of color @color in framebuffer at the index determined
 *  by @x and @y coordinates.
 *
 */

void tputchar_at(char c, unsigned short color, unsigned x, unsigned y) {

    const unsigned index = y * VGA_WIDTH + x;
    fbuffer[index] = vga_entry(c, color);

}

/*
 * tscroll_up:
 * -----------
 *
 *  Scroll the first 24 lines and delete the content of the last line.
 *
 */

void tscroll_up(void) {

    unsigned i;
    
    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT - 80; i++)
        fbuffer[i] = fbuffer[i + 80];

    for (i = 0; i < VGA_WIDTH; i++)
        fbuffer[(VGA_HEIGHT - 1) * VGA_WIDTH + 1] = vga_entry(' ', terminal_color);

}

/*
 * tpuchar:
 * --------
 *
 *  Wrapper function over tputchar_at. Puts the character in framebuffer and
 *  furthermore supports newline characters and scrolling the screen up.
 *
 */

void tputchar(char c) {

    if (terminal_column == VGA_WIDTH || c == '\n') {
        
        terminal_column = 0;

        if (terminal_row == VGA_HEIGHT - 1)
            tscroll_up();
        else
            terminal_row++;

    }

    if (c == '\n')
        return;

    tputchar_at(c, terminal_color, terminal_column++, terminal_row);

}

