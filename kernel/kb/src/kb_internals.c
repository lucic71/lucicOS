#include "kb_internals.h"

#include "kb_ports.h"
#include "kb_codes.h"

#include "lib/memio.h"

/*
 * _get_scancode:
 * --------------
 *
 *  Read from KB_DATA_PORT until a nonzero value comes.
 *
 */

uint8_t _get_scancode(void) {

    uint8_t code = 0;

    do {

        code = inb(KB_DATA_PORT);
        if (code) break;

    } while (1);

    return code;

}

/*
 * _process_scancode:
 * ------------------
 *
 *  Should set or unset each bit described in kb_codes.h.
 *
 *  side effects:
 *   changed the global variable @keystate.
 *
 */

void _process_scancode(uint8_t scancode) {

    if (scancode & SCANCODE_RELEASED)
        keystate &= ~KEYSTATE_PRESSED;
    else
        keystate |= KEYSTATE_PRESSED;

    /* Discard released/hit bit to work with the switch cases. */

    scancode &= 0X7F;

    if (keystate & KEYSTATE_PRESSED) {

        switch (scancode) {

            case SCANCODE_CTRL:
                keystate |= KEYSTATE_CTRL_PRESSED;
                break;

            case SCANCODE_LSHIFT:
            case SCANCODE_RSHIFT:
                keystate |= KEYSTATE_SHIFT_PRESSED;
                break;

            case SCANCODE_ALT:
                keystate |= KEYSTATE_ALT_PRESSED;
                break;

            case SCANCODE_CAPS:
                keystate = (keystate & KEYSTATE_CAPS_LOCKED) ?
                    keystate & ~KEYSTATE_CAPS_LOCKED :
                    keystate | KEYSTATE_CAPS_LOCKED;
                break;

            default:
                break;

        }

    } else {

        switch (scancode) {

            case SCANCODE_CTRL:
                keystate &= ~KEYSTATE_CTRL_PRESSED;
                break;

            case SCANCODE_LSHIFT:
            case SCANCODE_RSHIFT:
                keystate &= ~KEYSTATE_SHIFT_PRESSED;
                break;

            case SCANCODE_ALT:
                keystate &= ~KEYSTATE_ALT_PRESSED;
                break;

            default:
                break;

        }

    }

}

/*
 * _to_ascii:
 * ----------
 *
 *  Using the translation tables, keycode and keyshift, and keystate, convert
 *  scancode to ascii char.
 *
 */

uint8_t _to_ascii(uint8_t scancode) {

    uint8_t ascii_code = keycode[scancode];

    if (ascii_code == 0xFF)
        return ascii_code;

    if (ascii_code >= 'a' && ascii_code <= 'z' && ((keystate & KEYSTATE_CAPS_LOCKED)
                || (keystate & KEYSTATE_SHIFT_PRESSED)))
        ascii_code += 'A' - 'a';

    else if ((keystate & KEYSTATE_SHIFT_PRESSED) && keyshift[ascii_code] != 0xFF)
        ascii_code = keyshift[ascii_code];

    return ascii_code;

}
