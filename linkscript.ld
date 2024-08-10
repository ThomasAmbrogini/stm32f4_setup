ENTRY(_Reset)

MEMORY {
    FLASH (rx) : ORIGIN = 0x80000000, LENGTH = 512K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS {

    .text {
        _text_start = .;
        *(.vector_table)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _text_end = .;
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text)) {
        _data_start = .;
        *(.data)
        . = ALIGN(4);
        _data_end = .;
    } > RAM

    .bss {
        _bss_start = .;
        *(.bss)
        . = ALIGN(4);
        _bss_end = .;
    } > RAM

    _fiq_stack_start = ADDR(.bss) + SIZEOF(.bss);
    _fiq_stack_end = _fiq_stack_start + 0x1000; /* 4 KB */

    _irq_stack_start = _fiq_stack_end;
    _irq_stack_end = _irq_stack_start + 0x1000; /* 4 KB */

    _stack_start = _irq_stack_end;
    _stack_end = _stack_start + 0x1000; /* 4 KB */

    _irq_stack_size = _irq_stack_end - _irq_stack_start;
    _fiq_stack_size = _fiq_stack_end - _fiq_stack_start;

}

