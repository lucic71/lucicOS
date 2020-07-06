#ifndef KB_INTERNALS_H_
#define KB_INTERNALS_H_

#include "kernel/kb.h"
#include "kb_tables.h"
#include "kb_codes.h"
#include "kb_shortcut.h"

#include <stdint.h>
#include <stddef.h>

/*
 * Translation tables.
 *
 * keycode - scancode to ascii
 * keyshift - character when shift is pressed.
 *
 */

uint8_t keycode[KEYCODE_TABLE_SIZE];
uint8_t keyshift[KEYCODE_TABLE_SIZE];

/*
 * kb_shortcut - Table containing shortcuts
 * kb_shortcut_ptr - Index pointer to an available entry
 *
 */

kb_shortcut_t kb_shortcut[SHORTCUT_TABLE_SIZE];
size_t kb_shortcut_ptr;

/*
 * keystate:
 *  Bitfield containing the following information:
 *      - current key is pressed
 *      - ctrl is pressed
 *      - shift is pressed
 *      - alt is pressed
 *      - caps lock is on/off
 *
 */

uint8_t keystate;

/*
 * _get_scancode:
 *  
 *
 * @return - Scancode for the pressed key.
 *
 */

uint8_t _get_scancode(void);

/*
 * _process_scancode:
 *  Set keystate bitfield using the scancode.
 *
 * @param scancode - Current scancode
 *
 */

void _process_scancode(uint8_t scancode);

/*
 * _to_ascii:
 *  Converts a scancode to a ascii code.
 *
 * @param scancode - Current scancode
 * @return         - Ascii code for character if scancode valid
 *                   0xFF else
 *
 */

uint8_t _to_ascii(uint8_t scancode);

/*
 * _is_pressed:
 * 
 *
 * @return - 1 if key is pressed
 *           0 else
 *
 */

static inline int _is_pressed(uint8_t keystate) {

    return keystate & KEYSTATE_PRESSED;

}

/*
 * _is_backspace
 *  
 *
 * @return - 1 if scancode is for backspace
 *           0 else
 *
 */

static inline int _is_backspace(uint8_t scancode) {

    return scancode == SCANCODE_BACKSPACE;

}

/*
 * _is_sequence_released:
 *  Tests if a key is released after being pressed one or more times.
 *
 * @param scancode      - Current scancode
 * @param prev_scancode - Previous scancode
 *
 */

static inline int _is_sequence_released(uint8_t scancode,
        uint8_t prev_scancode) {
    
    return
        ((scancode & SCANCODE_RELEASED) && !(prev_scancode & SCANCODE_RELEASED)
        && ((scancode & ~SCANCODE_RELEASED) == prev_scancode));

}


#endif
