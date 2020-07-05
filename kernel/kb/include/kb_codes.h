#ifndef KB_KEYS_H_
#define KB_KEYS_H_

/* keystate bitfield macros. */

#define KEYSTATE_PRESSED 0x01
#define KEYSTATE_CTRL_PRESSED 0X02
#define KEYSTATE_SHIFT_PRESSED 0x04
#define KEYSTATE_ALT_PRESSED 0X08
#define KEYSTATE_CAPS_LOCKED 0x10

/* Important scancodes. */

#define SCANCODE_RELEASED 0x80
#define SCANCODE_CTRL 0x1D
#define SCANCODE_LSHIFT 0X2A
#define SCANCODE_RSHIFT 0X36
#define SCANCODE_ALT 0X38
#define SCANCODE_CAPS 0x3A

#endif
