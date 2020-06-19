#ifndef TERMINAL_H_
#define TERMINAL_H_

/*
 * tinit:
 *  Initializes the terminal.
 *
 */

void tinit(void);

/*
 * write:
 *  Writes the given buffer @buf of length @len on the screen, automatically
 *  advancing the cursor and scrolling the screen if necessary.
 *
 * @param buf - The buffer containing the data to be displayed
 * @param len - Length of the buffer.
 *
 */

int twrite(char *buf, unsigned int len);

#endif
