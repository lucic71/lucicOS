.global _start

/* Entry point in the kernel. */

.extern kmain

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

    kstack: .skip KSTACK_SIZE

/* Set the stack and call kmain. */

.text

_start:

    mov $kstack, %esp
    add $KSTACK_SIZE, %esp

    call kmain
    cli

.halt:
    jmp .halt
