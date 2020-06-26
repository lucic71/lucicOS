#include "vga.h"

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {

    return fg | (bg << 4);

}

uint16_t vga_entry(char c, uint8_t color) {

    return (uint16_t) c | ((uint16_t) color << 8);

}
