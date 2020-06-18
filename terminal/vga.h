#ifndef VAG_H_
#define VAG_H_

/*
 * Definition of an enum type that contains codes for each VGA color.
 *
 */

enum vga_colour {

    VGA_COLOUR_BLACK,
    VGA_COLOUR_BLUE,
    VGA_COLOUR_GREEN,
    VGA_COLOUR_CYAN,
    VGA_COLOUR_RED,
    VGA_COLOUR_MAGENTA,
    VGA_COLOUR_BROWN,
    VGA_COLOUR_LIGHT_GREY,
    VGA_COLOUR_DARK_GREY,
    VGA_COLOUR_LIGHT_BLUE,
    VGA_COLOUR_LIGHT_GREEN,
    VGA_COLOUR_LIGHT_CYAN,
    VGA_COLOUR_LIGHT_RED,
    VGA_COLOUR_LIGHT_MAGENTA,
    VGA_COLOUR_LIGHT_BROWN,
    VGA_COLOUR_WHITE,

};

/*
 * vga_entry_color:
 *  Creates a VGA color encoding by combining foreground and background colors.
 *
 * @param fg - Foreground color
 * @param bg - Background color
 * @return   - Combined encoding
 *
 */

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);

/*
 * vga_entry:
 *  Creates a VGA entry from the character @c and the color associated with 
 *  it, @color.
 *
 * @param c     - Character
 * @param color - Color of the character
 * @return      - VGA entry
 *
 */

uint8_t vga_entry(unsigned char c, uint8_t color);

#endif
