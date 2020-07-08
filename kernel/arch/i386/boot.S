.global _start

/* Entry point in the kernel. */

.extern kmain

/* Symbols used to jump/return to/from gdt_init. */

.extern gdt_init
.global gdt_return

/*
 * GRUB will load the kernel only if it compiles with the multiboot spec.
 * The header must contain a magic number, a flag (which can be set to 0x00)
 * and the checksum (checksum = - (flag + magic_number))
 *
 */

.set MAGIC_NUMBER, 0x1BADB002
.set FLAGS,        0x00
.set CHECKSUM,     -(MAGIC_NUMBER + FLAGS)



/*
 * Put the header in multiboot section so that it is placed in the first 8Kib
 * of the executable.
 *
 */

.section .multiboot
    .align 4

    .int MAGIC_NUMBER
    .int FLAGS
    .int CHECKSUM

/* Create a kstack so that the entry point in the kernel can be called. */

.set KSTACK_SIZE, 4096

.bss
    .align 16

    multiboot_hdr_ptr: .skip 4
    multiboot_magic:   .skip 4

    kstack: .skip KSTACK_SIZE


/* 
 * Set up GDT and the stack, after that kmain can be called with its corresponding
 * multiboot arguments.
 *
 */

.text

_start:

    mov %eax, multiboot_magic
    mov %ebx, multiboot_hdr_ptr

    /* Use a jmp instead of call because there is no valid stack. */

    cli
    jmp gdt_init

gdt_return:

    sti

stack_init:

    /* Set the stack pointer to the top of the stack declared in bss. */

    mov $kstack, %esp
    add $KSTACK_SIZE, %esp

kentry:

    /* Set ebp to 0 to start the backtrace in kmain. */

    xor %ebp, %ebp

    /* kmain multiboot arguments. */

    pushl multiboot_magic
    pushl multiboot_hdr_ptr

    /*
     * Now that we are in protected mode and the stack is set up we cann call
     * the kernel entry point.
     *
     */

    call kmain

.halt:
    jmp .halt

