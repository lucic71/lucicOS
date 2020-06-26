#include "screen.h"
#include "serial.h"

void kmain(void) {

    screen_init();
    screen_write("buna ziua", sizeof("buna ziua") - 1);

    serial_init(COM1);
    serial_write(COM1, "buna ziua", sizeof("buna ziua") - 1);
}
