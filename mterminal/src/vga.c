#include "vga.h"

unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg) {

    return fg | (bg << 4);

}

unsigned short vga_entry(unsigned char c, unsigned char color) {

    return (unsigned short) c | ((unsigned short) color << 8);

}
