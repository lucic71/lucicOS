#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdint.h>

/* register_t - data type containg the context before calling an ISR or IRQ. */

struct context {

    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;

} __attribute__((packed));

typedef struct context context_t;

#endif
