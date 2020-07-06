#ifndef KB_SHORTCUT_H_
#define KB_SHORTCUT_H_

/* Typedef for shortcut handler routine. */

typedef void (* shortcut_handler_t) (void *);

/*
 * kb_shortcut_struct:
 *  Data type used to register a keyboard shortcut.
 *
 */

struct kb_shortcut_struct {

    uint8_t scancode;
    uint8_t keystate;
    shortcut_handler_t handler;
    void *arg;

};

typedef struct kb_shortcut_struct kb_shortcut_t;

/*
 * _register_shortcut:
 *  Registers a keyboard shortcut.
 *
 * @param scancode - Scancode for shortcut
 * @param keystate - Keystate for shortcut
 * @param handler  - Handler routine for shortcut
 * @param arg      - Argument for handler
 *
 * @return         - 0 if successful
 *                   1 else
 *
 */

int _register_shortcut(uint8_t scancode, uint8_t keystate,
        shortcut_handler_t handler, void *arg);

/*
 * _execute_shortcut:
 *  Finds and executes a shortcut.
 *
 * @param scancode - Scancode for shortcut
 * @param keystate - Keystate for shortcut
 *
 * @return         - 0 if successful
 *                   1 else
 *
 */

int _execute_shortcut(uint8_t scancode, uint8_t keystate);

#endif
