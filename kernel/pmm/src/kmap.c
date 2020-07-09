#include "kernel/pmm.h"

#include <stdio.h>
#include <stdint.h>

extern uint8_t *_kernel_start;
extern uint8_t *_kernel_end;

extern uint8_t *_kernel_text_start;
extern uint8_t *_kernel_text_end;

extern uint8_t *_kernel_rodata_start;
extern uint8_t *_kernel_rodata_end;

extern uint8_t *_kernel_data_start;
extern uint8_t *_kernel_data_end;

extern uint8_t *_kernel_bss_start;
extern uint8_t *_kernel_bss_end;

void print_kernel_map(void) {

    printf("Kernel Memory Map:\n");
    printf("kernel: 0x%x - 0x%x\n", &_kernel_start, &_kernel_end);
    printf("text: 0x%x - 0x%x\n", &_kernel_text_start, &_kernel_text_end);
    printf("rodata: 0x%x - 0x%x\n", &_kernel_rodata_start, &_kernel_rodata_end);
    printf("data: 0x%x - 0x%x\n", &_kernel_data_start, &_kernel_data_end);
    printf("bss: 0x%x - 0x%x\n", &_kernel_bss_start, &_kernel_bss_end);

}
