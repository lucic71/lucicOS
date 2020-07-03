#ifndef A20_H_
#define A20_H_

/*
 * FAST_A20_GATE - I/O port used to read the state of the a20 line and to
 *  enable it if needed.
 *
 * A20_ENABLED_BIT - This value can be tested to check if the a20 line is
 *  enabled, if we want to enable it just OR the value read from the I/O
 *  port with A20_ENABLED_BIT and write the new value back in the port.
 *
 * FAST_RESET_MASK - It is important to unset the first bit of the byte
 *  written back in the port because it causes a fast reset, this is
 *  undesired when enabling the a20 line.
 *
 */

#define FAST_A20_GATE 0x92

#define A20_ENABLED_BIT 0x02
#define FAST_RESET_MASK 0x01

#endif
