#ifndef SERIAL_PORTS_H_
#define SERIAL_PORTS_H_

/* I/O port offsets. They are calculated relative to data port. */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_INTRPT_ENABLE_PORT(base) (base + 1)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#endif
