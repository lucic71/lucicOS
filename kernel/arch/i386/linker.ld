ENTRY(_start)

SECTIONS {

    /*
     * The code should be loaded at an address greater or equal to 1MB because
     * lower addresses are reserved to GRUB, BIOS and memory mapped I/O.
     *
     */

    . = 0x00100000;

    /* Align all sections from all files to a 4KB boundary. */

    _kernel_start = .;
    _kernel_text_start = .;

    .text ALIGN (0x1000) : {
        *(.multiboot)
        *(.text)
    }

    _kernel_text_end = .;
    _kernel_rodata_start = .;

    .rodata ALIGN (0x1000) : {
        *(.rodata*)
    }

    _kernel_rodata_end = .;
    _kernel_data_start = .;

    .data ALIGN (0x1000) : {
        *(.data)
    }

    _kernel_data_end = .;
    _kernel_bss_start = .;

    .bss ALIGN (0x1000) : {
        *(COMMON)
        *(.bss)
    }

    _kernel_bss_end = .;
    _kernel_end = .;

    /DISCARD/ : {
        *(.comment)
        *(.note.gnu.build-id)
    }

}

/*
 * Note:
 *  COMMON section keeps data objects that are not yet allocated,
 *  this is just a prelinking section, it will be transformed into bss
 *  and data after linking.
 *
 */
