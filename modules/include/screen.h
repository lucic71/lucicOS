#ifndef SCREEN_H_
#define SCREEN_H_

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
