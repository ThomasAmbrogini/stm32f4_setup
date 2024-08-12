ENTRY(resetHandler)

MEMORY {
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS {

      .isr_vector :
      {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) /* Startup code */
        . = ALIGN(4);
      } >FLASH

    .text : {
        . = ALIGN(4);
        _start_text = .;
        *(.text)
        *(.text*)
        *(.rodata)

        . = ALIGN(4);
        _end_text = .;
        _stored_data = .;
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text)) {
        _start_data = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _end_data = .;
    } > RAM

    .bss : {
        _start_bss = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _end_bss = .;
    } > RAM

    END_STACK = ORIGIN(RAM) + LENGTH(RAM);
}

