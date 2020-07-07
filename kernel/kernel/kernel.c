#include <stdio.h>

#include "kernel/screen.h"
#include "kernel/serial.h"
#include "kernel/kb.h"
#include "i386/isr.h"
#include "i386/irq.h"
#include "i386/idt.h"

void kmain(void) {

    idt_init();
    irq_init();
    isr_init();

    serial_init(COM1);

    screen_init();
    kb_init();

    printf("Welcome to lucicOS\n\n");
    printf("If you are using bochs as emulator, check bochs/serial.txt"
            " to see info about the interrupts\n");
    printf("Press CTRL + Backspace to dump registers:");

}
