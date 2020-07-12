#include "kernel/timer.h"

#include "timer_internals.h"

#include "kernel/screen.h"

#include "i386/irq.h"

#include "lib/memio.h"

#include <stdio.h>

static uint32_t tick;

/*
 * timer_intrpt_handler:
 * ---------------------
 *
 */

static void timer_intrpt_handler(__attribute__ ((unused)) context_t ctx) {

    tick++;
    screen_delete_line();
    printf("Tick: %d", tick);

}

/*
 * timer_init:
 * -----------
 *
 *  Register the IRQ and sent the frequency to PIT.
 *
 */

void timer_init(uint32_t freq) {

    register_irq(IRQ0, timer_intrpt_handler);

    outb(PIT_COMMAND_PORT, PIT_DIV_READY);

    uint16_t divisor = PIT_DEFAULT_FREQ / freq;

    uint8_t freq_low  = (uint8_t) (divisor & 0xFF);
    uint8_t freq_high = (uint8_t) (divisor >> 8);

    outb(PIT_CH0_DATA_PORT, freq_low);
    outb(PIT_CH0_DATA_PORT, freq_high);

}
