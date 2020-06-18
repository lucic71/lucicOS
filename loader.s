global loader

; Entry point in the kernel.

extern kmain

; GRUB will load the kernel only if it compiles with the multiboot spec.
; The header must contain a magic number, a flag (which can be set to 0x00)
; and the checksum (checksum = - (flag + magic_number))

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x00
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)

; Put the header in multiboot section so that it is placed in the first 8Kib
; of the executable.

section .multiboot
    align 4

    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

; Create a kstack so that the entry point in the kernel can be called.

KSTACK_SIZE equ 4096

section .bss
    align 4

    kstack resb KSTACK_SIZE

; Set the stack and call kmain.

section .text

loader:
    mov esp, kstack + KSTACK_SIZE
    call kmain

.halt:
    jmp .halt
