#ifndef LOG_H_
#define LOG_H_

#include <stdint.h>

/*
 * reg_dump:
 *  Dumps the content of general purpose registers on the screen.
 *
 * Argument became void * because this routine is used as a handeler for a 
 * keyboard shortcut that receives a pointer to void. Normally I would set
 * the argument to void.
 *
 */

void reg_dump(void *);

#endif
