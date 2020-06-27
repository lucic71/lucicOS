ENTRY(_start)

SECTIONS {

    /*
     * The code should be loaded at an address greater or equal to 1MB because
     * lower addresses are reserved to GRUB, BIOS and memory mapped I/O.
     *
     */

    . = 0x00100000;

    /*
     * Align all sections from all files to a 4KB boundary.
     *
     */

    .text ALIGN (0x1000) : {
        *(.multiboot)
        *(.text)
    }

    .rodata ALIGN (0x1000) : {
        *(.rodata*)
    }

    .data ALIGN (0x1000) : {
        *(.data)
    }

    /*
     * Note:
     *  COMMON section keeps data objects that are not yet allocated,
     *  this is just a prelinking section, it will be transformed into bss
     *  and data after linking.
     *
     */

    .bss ALIGN (0x1000) : {
        *(COMMON)
        *(.bss)
    }

}
