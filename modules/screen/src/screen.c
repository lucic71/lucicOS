#include "screen.h"

#include "framebuffer.h"
#include "cursor.h"

#include "vga.h"
#include "memio.h"

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

static void screen_putchar_at(char c, unsigned short color, unsigned x, unsigned y);
static void screen_putchar(char c);

static void screen_scroll_up(void);

/*
 * screen_init:
 * ------
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

    fbuffer = (unsigned short *) FBUFFER_START_ADDR;

    for (unsigned y = 0; y < VGA_HEIGHT; y++) {
        for (unsigned x = 0; x < VGA_WIDTH; x++) {

            const unsigned index = y * VGA_WIDTH + x;
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
        screen_putchar(buf[i]);

    return i;
}

/* PRIVATE FUNCTIONS */

/*
 * screen_putchar_at:
 * ------------------
 *
 *  Put the character @c of color @color in framebuffer at the index determined
 *  by @x and @y coordinates.
 *
 */

static void screen_putchar_at(char c, unsigned short color, unsigned x, unsigned y) {

    const unsigned index = y * VGA_WIDTH + x;
    fbuffer[index] = vga_entry(c, color);

}

/*
 * screen_scroll_up:
 * -----------------
 *
 *  Scroll the first 24 lines and delete the content of the last line.
 *
 */

static void screen_scroll_up(void) {

    unsigned i;
    
    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT - 80; i++)
        fbuffer[i] = fbuffer[i + 80];

    for (i = 0; i < VGA_WIDTH; i++)
        fbuffer[(VGA_HEIGHT - 1) * VGA_WIDTH + 1] = vga_entry(' ', screen_color);

}

/*
 * screen_puchar:
 * --------------
 *
 *  Wrapper function over screen_putchar_at. Puts the character in framebuffer and
 *  has support for newline characters.
 *
 *  Side efects:
 *   scrolls up the screen whenever there is no more space
 *   moves the cursor after each displayed characte
 *
 */

static void screen_putchar(char c) {

    if (screen_column == VGA_WIDTH || c == '\n') {
        
        screen_column = 0;

        if (screen_row == VGA_HEIGHT - 1)
            screen_scroll_up();
        else
            screen_row++;

    }

    if (c == '\n')
        return;

    screen_putchar_at(c, screen_color, screen_column++, screen_row);
    screen_move_cursor(screen_column, screen_row);

}
