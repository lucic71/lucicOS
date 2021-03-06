#ifndef SCREEN_H_
#define SCREEN_H_

#include "stddef.h"

/*
 * screen_init:
 *  Initializes the terminal.
 *
 */

void screen_init(void);

/*
 * screen_write:
 *  Writes the given buffer @buf of length @len on the screen, automatically
 *  advancing the cursor and scrolling the screen if necessary.
 *
 * @param buf - The buffer containing the data to be displayed
 * @param len - Length of the buffer.
 * @return    - The number of written bytes
 *
 */

size_t screen_write(char *buf, size_t len);

/*
 * screen_delete:
 *  Deletes the current character and updates the position of the cursor.
 *
 */

void screen_delete(void);

/*
 * screen_delete_line:
 *  Deletes current line and updates the position of the cursor. The cursor
 *  will be placed at the beginning of the current line after this routine
 *  ends.
 *
 */

void screen_delete_line(void);

#endif
