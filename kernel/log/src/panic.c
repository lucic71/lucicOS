#include "kernel/log.h"

#include <stdio.h>

void panic(char *panic_str) {

    printf("\nPanic: %s\n", panic_str);
    while (1);

}
