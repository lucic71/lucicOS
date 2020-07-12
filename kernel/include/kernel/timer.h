#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

/*
 * timer_init:
 *  Initializes the timer to a give tick frequency.
 *
 * @param freq - Frequency
 *
 */

void timer_init(uint32_t freq);

#endif
