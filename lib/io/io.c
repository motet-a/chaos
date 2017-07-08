/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <chaosdef.h>
#include <lib/io.h>

static void
default_putc(char c __unused)
{}

static void
default_puts(char const *str __unused)
{}

static char
default_getc(void)
{
  return (0);
}

static struct io_output_callbacks	serial_cb = {
	.putc = &default_putc,
	.puts = &default_puts,
};

static struct io_output_callbacks	console_cb = {
	.putc = &default_putc,
	.puts = &default_puts,
};

static struct io_input_callbacks	input_cb = {
	.getc = &default_getc,
};

void
io_putc(char c)
{
	serial_cb.putc(c);
	console_cb.putc(c);
}

void
io_puts(char const *s)
{
	serial_cb.puts(s);
	console_cb.puts(s);
}

char
io_getc(void)
{
	return (input_cb.getc());
}

void
register_io_output_callbacks(struct io_output_callbacks *cb, enum io_output_types type)
{
	if (type == IO_OUTPUT_SERIAL) {
		serial_cb = *cb;
	} else {
		console_cb = *cb;
	}
}

void
register_io_input_callbacks(struct io_input_callbacks *cb)
{
	input_cb = *cb;
}
