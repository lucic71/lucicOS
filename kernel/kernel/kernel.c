#include <stdio.h>
#include <stdint.h>

#include "kernel/screen.h"
#include "kernel/serial.h"
#include "kernel/kb.h"
#include "kernel/multiboot.h"
#include "kernel/log.h"
#include "kernel/pmm.h"

#include "i386/isr.h"
#include "i386/irq.h"
#include "i386/idt.h"

void kmain(multiboot_info_t *mb_info, uint32_t mb_magic) {

    idt_init();
    irq_init();
    isr_init();

    screen_init();

    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC)
        panic("Not a multiboot bootloader!");

    if (!mb_info)
        panic("Invalid multiboot pointer");

    if (!(mb_info->flags & MULTIBOOT_INFO_MEMORY))
        panic("There is no memory info in multiboot");

    printf("mem_lower: 0x%x B, mem_upper: 0x%x B\n\n", mb_info->mem_lower * 1024, mb_info->mem_upper * 1024);
    print_memory_map((multiboot_memory_map_t *) mb_info->mmap_addr,
            (multiboot_memory_map_t *) (mb_info->mmap_addr + mb_info->mmap_length));
    puts("");
    print_kernel_map();

    serial_init(COM1);

    kb_init();

    printf("\nWelcome to lucicOS\n\n");
    printf("If you are using bochs as emulator, check bochs/serial.txt"
            " to see info about the interrupts\n");
    printf("Press CTRL + Backspace to dump registers:");

}
