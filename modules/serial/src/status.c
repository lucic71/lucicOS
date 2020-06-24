#include "status.h"
#include "ports.h"
#include "commands.h"

#include "memio.h"

int serial_is_transmit_fifo_empty(uint16_t com) {

    return (inb(SERIAL_LINE_STATUS_PORT(com)) & LINE_STATUS_FIFO_EMPTY ) > 0;

}

