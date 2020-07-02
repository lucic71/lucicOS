#ifndef VGA_H_
#define VGA_H_

#include "stdint.h"

/*
 * Definition of an enum type that contains codes for each VGA color.
 *
 */

enum vga_color {

    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE,

};

/*
 * Use the classic 80x25 mode for screen size.
 *
 */

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

/*
 * vga_entry_color:
 *  Creates a VGA color encoding by combining foreground and background colors.
 *
 * @param fg - Foreground color
 * @param bg - Background color
 * @return   - Combined encoding
 *
 */

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {

    return fg | (bg << 4);

}

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

static inline uint16_t vga_entry(char c, uint8_t color) {

    return (uint16_t) c | ((uint16_t) color << 8);

}

#endif
