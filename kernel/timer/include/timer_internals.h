#ifndef TIMER_INTERNALS_H_
#define TIMER_INTERNALS_H_

/* Command ports. */

#define PIT_COMMAND_PORT 0x43

/* Data ports. */

#define PIT_CH0_DATA_PORT 0x40
#define PIT_CH1_DATA_PORT 0x41
#define PIT_CH2_DATA_PORT 0x42

/* Command bytes. */

#define PIT_DIV_READY 0x36

/* Default frequency of PIT's internal clock. */

#define PIT_DEFAULT_FREQ 1193180

#endif
