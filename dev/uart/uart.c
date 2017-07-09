/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <asm.h>
#include <dev/uart.h>
#include <lib/io.h>

# define COM1			0x3F8 /* COM1 Port */

static int
uart_putc(int c)
{
	outb(COM1, c);
	return (1);
}

static int
uart_puts(char const *str)
{
	char const *s;

	s = str;
	while (*str) {
		outb(COM1, *str);
		++str;
	}
	return (str - s);
}

static void
uart_init(enum init_level il __unused)
{
	struct io_output_callbacks cb;

	cb.putc = &uart_putc;
	cb.puts = &uart_puts;
	outb(COM1 + 1, 0x00);	/* Disable all interrupts			*/
	outb(COM1 + 3, 0x80);	/* Enable DLAB (set baud rate divisor)		*/
	outb(COM1 + 0, 0x03);	/* Set divisor to 3 (lo byte) 38400 baud	*/
	outb(COM1 + 1, 0x00);	/*                  (hi byte)			*/
	outb(COM1 + 3, 0x03);	/* 8 bits, no parity, one stop bit		*/
	outb(COM1 + 2, 0xC7);	/* Enable FIFO, clear them, with 14-byte threshold */
	outb(COM1 + 4, 0x0B);	/* IRQs enabled, RTS/DSR set);			*/

	if(inb(COM1 + 5) != 0xFF) {
		register_io_output_callbacks(&cb, IO_OUTPUT_SERIAL);
	}
}

NEW_DEV_HOOK(uart, &uart_init, CHAOS_INIT_LEVEL_DEV_EARLY);
