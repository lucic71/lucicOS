#include <stdio.h>
#include <stdint.h>

#include "kernel/screen.h"
#include "kernel/serial.h"
#include "kernel/kb.h"
#include "kernel/multiboot.h"
#include "kernel/log.h"
#include "kernel/pmm.h"
#include "kmain/multiboot.h"

#include "i386/isr.h"
#include "i386/irq.h"
#include "i386/idt.h"


void kmain(multiboot_info_t *mb_info, uint32_t mb_magic) {

    /* Interrupt initialization. */

    idt_init();
    irq_init();
    isr_init();

    /* Screen initialization. */

    screen_init();

    /* Multiboot initialization. */

    multiboot_init(mb_info, mb_magic);

    /* Physical memory manager initialization. */

    print_memory_map(mb_info->mmap_addr,
             mb_info->mmap_addr + mb_info->mmap_length);
    puts("");
    print_kernel_map();

    uint32_t mem_size = 1024 + mb_info->mem_upper;
    extern uint8_t *_kernel_end;

    pmm_init((uint32_t) &_kernel_end, mem_size);

    pmm_init_available_regions(mb_info->mmap_addr,
            mb_info->mmap_addr + mb_info->mmap_length);
    pmm_deinit_kernel();

    /* Serial initialiation. */

    serial_init(COM1);

    /* Keyboard initialiation. */

    kb_init();

    printf("\nWelcome to lucicOS\n\n");
    printf("If you are using bochs as emulator, check bochs/serial.txt"
            " to see info about the interrupts\n");
    printf("Press CTRL + Backspace to dump registers:");

}
