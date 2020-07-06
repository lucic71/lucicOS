#ifndef KB_H_
#define KB_H_

#include <stdint.h>

/*
 * kb_init:
 *  Initializes the keyboard module and registers the IRQ.
 *  It alsor registers some keyboard shortcuts.
 *
 *  Currently this drive only supports PS2 keyboards with
 *  scan code set 1.
 *
 */

void kb_init(void);

#endif
