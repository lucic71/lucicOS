#include "kb_internals.h"

#include "kb_codes.h"

/*
 * _register_shortcut:
 * -------------------
 *
 *  Make sure that PRESSED bit is set in keystate. If there is already a
 *  handler for the same scancode and keystate, update its handler routine
 *  and its handler routine argument.
 *
 *  Otherwise put the handler on the next free position. THe routine returns
 *  a positive number if an error occurs.
 *
 */

int _register_shortcut(uint8_t scancode, uint8_t keystate,
        void (*handler) (void *), void *arg) {

    keystate |= KEYSTATE_PRESSED;

    size_t i = 0;
    for ( ; i < kb_shortcut_ptr; i++)
        if (kb_shortcut[i].scancode == scancode &&
                kb_shortcut[i].keystate == keystate)
            break;

    if (i < kb_shortcut_ptr) {

        kb_shortcut[i].handler = handler;
        kb_shortcut[i].arg = arg;
        return 0;

    }

    if (kb_shortcut_ptr == SHORTCUT_TABLE_SIZE)
        // TODO: a robust error handler
        return 1;

    kb_shortcut[kb_shortcut_ptr] =
        (kb_shortcut_t) {scancode, keystate, handler, arg};

    kb_shortcut_ptr++;

    return 0;

}

/*
 * _execute_shortcut:
 * ------------------
 *
 *  Find the corresponding handler for scancode and keystate and execute it.
 *
 */

int _execute_shortcut(uint8_t scancode, uint8_t keystate) {

    size_t i = 0;
    for ( ; i < kb_shortcut_ptr; i++)
        if (kb_shortcut[i].scancode == scancode &&
                kb_shortcut[i].keystate == keystate)
            break;

    if (i < kb_shortcut_ptr && kb_shortcut[i].handler) {
        kb_shortcut[i].handler(kb_shortcut[i].arg);
        return 0;
    }

    return 1;

}
