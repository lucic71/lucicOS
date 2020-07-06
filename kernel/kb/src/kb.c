#include "kernel/kb.h"
#include "kernel/screen.h"
#include "kernel/log.h"

#include "kb_internals.h"
#include "kb_shortcut.h"

#include "i386/context.h"
#include "i386/irq.h"

#include "lib/memio.h"

#include <stddef.h>

/*
 * kb_intrpt_handler:
 * ------------------
 *
 *  Using a current fetched scancode and a previous fetched scancode,
 *  update the keystate and convert a current scancode if its corresponding
 *  key has not yet been released.
 *
 *  Aftter the _is_sequence_released check, the routine checks if there is
 *  and shortcut associated with the current scancode and keystate, if so
 *  it executes it and returns.
 *
 *  It also supports special characters, ex: backspace.
 *
 */

void kb_intrpt_handler(__attribute__ ((unused)) context_t context) {

    static uint8_t prev_scancode;

    uint8_t scancode = _get_scancode();
    _process_scancode(scancode);

    if (_is_sequence_released(scancode, prev_scancode)) {

        prev_scancode = scancode;
        return;

    }

    if (!_execute_shortcut(scancode, keystate))
        return;

    uint8_t asciicode = _to_ascii(scancode);

    if (_is_backspace(scancode))
        screen_delete();

    else if (_is_pressed(keystate) && asciicode != 0xFF)
        screen_write((char *) &asciicode, 1);

    prev_scancode = scancode;

}

/*
 * kb_init:
 * --------
 *
 *  Fill the translation tables and register the keyboard interrupt.
 *  Register shortcuts.
 *
 *  keycode and keyshift will be filled with the default value 0xFF. Later,
 *  keycode will be filled with the corresponding ascii codes for each
 *  scancode and keyshift with the corresponding shift character for each
 *  scancode.
 *
 */

void kb_init(void) {

    for (int i = 0; i < KEYCODE_TABLE_SIZE; i++)
        keycode[i] = keyshift[i] = 0xFF;

    keycode[0x02] = '1';
    keycode[0x03] = '2';
    keycode[0x04] = '3';
    keycode[0x05] = '4';
    keycode[0x06] = '5';
    keycode[0x07] = '6';
    keycode[0x08] = '7';
    keycode[0x09] = '8';

    keycode[0x0a] = '9';
    keycode[0x0b] = '0';
    keycode[0x0c] = '-';
    keycode[0x0d] = '=';
    keycode[0x0f] = '\t';
    keycode[0x10] = 'q';
    keycode[0x11] = 'w';
    keycode[0x12] = 'e';

    keycode[0x13] = 'r';
    keycode[0x14] = 't';
    keycode[0x15] = 'y';
    keycode[0x16] = 'u';
    keycode[0x17] = 'i';
    keycode[0x18] = 'o';
    keycode[0x19] = 'p';
    keycode[0x1a] = '[';

    keycode[0x1b] = ']';
    keycode[0x1c] = '\n';
    keycode[0x1e] = 'a';
    keycode[0x1f] = 's';
    keycode[0x20] = 'd';
    keycode[0x21] = 'f';
    keycode[0x22] = 'g';
    keycode[0x23] = 'h';

    keycode[0x24] = 'j';
    keycode[0x25] = 'k';
    keycode[0x26] = 'l';
    keycode[0x27] = ';';
    keycode[0x28] = '\'';
    keycode[0x29] = '`';
    keycode[0x2b] = '\\';
    keycode[0x2c] = 'z';

    keycode[0x2d] = 'x';
    keycode[0x2e] = 'c';
    keycode[0x2f] = 'v';
    keycode[0x30] = 'b';
    keycode[0x31] = 'n';
    keycode[0x32] = 'm';
    keycode[0x33] = ',';
    keycode[0x34] = '.';

    keycode[0x35] = '/';
    keycode[0x39] = ' ';

    keyshift['`'] = '~';
    keyshift['1'] = '!';
    keyshift['2'] = '@';
    keyshift['3'] = '#';
    keyshift['4'] = '$';
    keyshift['5'] = '%';
    keyshift['6'] = '^';
    keyshift['7'] = '&';

    keyshift['8'] = '*';
    keyshift['9'] = '(';
    keyshift['0'] = ')';
    keyshift['-'] = '_';
    keyshift['='] = '+';
    keyshift['['] = '{';
    keyshift[']'] = '}';
    keyshift['\\'] = '|';

    keyshift[';'] = ':';
    keyshift['\''] = '"';
    keyshift[','] = '<';
    keyshift['.'] = '>';
    keyshift['/'] = '?';

    _register_shortcut(SCANCODE_BACKSPACE, KEYSTATE_CTRL_PRESSED,
            reg_dump, (void *) 0);

    register_irq(IRQ1, kb_intrpt_handler);

}
