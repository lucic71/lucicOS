#ifndef KB_H_
#define KB_H_

#include <stdint.h>

/*
 * kb_init:
 *  Initializes the keyboard module and registers the IRQ.
 *
 *  Currently this drive only supports PS2 keyboards with
 *  scan code set 1.
 *
 */

void kb_init(void);

/*
 * kb_shortcut_struct:
 *  Data type used to register a keyboard shortcut.
 *
 */

struct kb_shortcut_struct {

    uint8_t scancode;
    uint8_t keystate;
    void (*handler) (void *);
    void *arg;

};

typedef struct kb_shortcut_struct kb_shortcut_t;

/*
 * register_shortcut:
 *  Registers a keyboard shortcut.
 *
 * @param scancode - Scancode for shortcut
 * @param keystate - Keystate for shortcut
 * @param handler  - Handler routine for shortcut
 * @param arg      - Argument for handler
 *
 */

int register_shortcut(uint8_t scancode, uint8_t keystate,
        void (*handler) (void *), void *arg);

#endif
