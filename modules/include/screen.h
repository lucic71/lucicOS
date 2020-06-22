#ifndef SCREEN_H_
#define SCREEN_H_

/*
 * The starting address of the memory mapped I/O for the framebuffer.
 *
 */

#define FBUFFER_START_ADDR 0x000B8000

/*
 * sinit:
 *  Initializes the terminal.
 *
 */

void sinit(void);

/*
 * swrite:
 *  Writes the given buffer @buf of length @len on the screen, automatically
 *  advancing the cursor and scrolling the screen if necessary.
 *
 * @param buf - The buffer containing the data to be displayed
 * @param len - Length of the buffer.
 *
 */

int swrite(char *buf, unsigned int len);

#endif