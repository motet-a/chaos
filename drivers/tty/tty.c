/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/linker.h>
#include <drivers/drivers.h>
#include <drivers/tty.h>
#include <lib/io.h>

/* Global definitions */
static struct tty tty;
static uint const	TTY_WIDTH	= 80;
static uint const	TTY_HEIGHT	= 25;
static uint16 *const	TTY_BUFFER	= (uint16*)((char *)KERNEL_VIRTUAL_BASE + 0xB8000);

/*
** Set the current color, for future outputs
*/
void
tty_set_color(enum TTY_COLOR fg, enum TTY_COLOR bg)
{
	tty.vga_attrib = ((bg << 4u) | (fg & 0x0F)) << 8u;
}

/*
** Clear the screen
*/
void
tty_clear(void)
{
	uint i;
	uint16 blank;

	i = 0;
	blank = tty.vga_attrib | 0x20;
	while (i < TTY_WIDTH * TTY_HEIGHT)
	{
		*(tty.vgabuff + i) = blank;
		++i;
	}
}

/*
** Print a single character on the screen
*/
static int
tty_putchar(int c)
{
	switch (c)
	{
	case '\n':
		tty.cursor_x = 0;
		tty.cursor_y++;
		break;
	default:
		*(tty.vgabuff + tty.cursor_y * TTY_WIDTH + tty.cursor_x) =
			tty.vga_attrib | (uchar)c;
		tty.cursor_x += 1;
		break;
	}
	tty.cursor_y += (tty.cursor_x >= TTY_WIDTH);
	tty.cursor_x *= (tty.cursor_x < TTY_WIDTH);
	while (tty.cursor_y >= TTY_HEIGHT) {
		/* TODO add scroll here */
		tty.cursor_y -= 1;
	}
	return (1);
}

/*
** Print an array of character on the screen
*/
static int
tty_puts(char const *str)
{
	char const *s;

	s = str;
	while (*str) {
		tty_putchar(*str);
		++str;
	}
	return (str - s);
}

/*
** Initialize the tty driver
*/
static void
tty_init(enum init_level il __unused)
{
	struct io_output_callbacks cb;

	cb.putc = tty_putchar;
	cb.puts = tty_puts;
	tty.vgabuff = TTY_BUFFER;
	tty_set_color(TTY_WHITE, TTY_DARK_GREY);
	tty_clear();
	register_io_output_callbacks(&cb, IO_OUTPUT_CONSOLE);
}

NEW_DRIVER_HOOK(tty_init, &tty_init, CHAOS_INIT_LEVEL_DRIVER_EARLY);
