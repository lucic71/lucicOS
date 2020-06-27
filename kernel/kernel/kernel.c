#include "kernel/screen.h"

void kmain(void) {

    screen_init();
    screen_write("aa", 2);

}
