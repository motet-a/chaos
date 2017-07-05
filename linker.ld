/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

KERNEL_VIRTUAL_LINK = 0xC0100000;
KERNEL_VIRTUAL_BASE = 0xC0000000;

OUTPUT_FORMAT(elf32-i386);
ENTRY(start)

SECTIONS
{
  . = KERNEL_VIRTUAL_LINK;

  .text ALIGN(0x1000) : AT(ADDR(.text) - KERNEL_VIRTUAL_BASE)
  {
    *(.text)
  }

  .rodata ALIGN(0x1000) : AT(ADDR(.rodata) - KERNEL_VIRTUAL_BASE)
  {
    *(.rodata)
  }

  .data ALIGN(0x1000) : AT(ADDR(.data) - KERNEL_VIRTUAL_BASE)
  {
    *(.data)
  }

  .bss ALIGN(0x1000) : AT(ADDR(.bss) - KERNEL_VIRTUAL_BASE) {
    *(COMMON)
    *(.bss)
  }
  KERNEL_VIRTUAL_END = .;
  KERNEL_PHYSICAL_END = . - KERNEL_VIRTUAL_BASE;
}
