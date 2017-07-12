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
#include <string.h>

/* Global definitions */
static struct tty tty;
static uint const	TTY_WIDTH	= 80;
static uint const	TTY_HEIGHT	= 25;
static uint16 *const	TTY_BUFFER	= (uint16*)((char *)KERNEL_VIRTUAL_BASE + 0xB8000);

/*
** Sets the current color for next outputs
*/
void
tty_set_color(enum TTY_COLOR fg, enum TTY_COLOR bg)
{
	tty.vga_attrib = ((bg << 4u) | (fg & 0x0F)) << 8u;
}

/*
** Clears the screen
*/
void
tty_clear(void)
{
	uint i;
	uint16 blank;

	i = 0;
	blank = tty.vga_attrib | 0x20;
	while (i < TTY_WIDTH)
	{
		*(tty.vgabuff + i) = blank;
		++i;
	}
	i = 1;
	while (i < TTY_HEIGHT)
	{
		memcpy(tty.vgabuff + TTY_WIDTH * i, tty.vgabuff, sizeof(*tty.vgabuff) * TTY_WIDTH);
		++i;
	}
}

/*
** Prints a single character on the screen
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
** Prints an array of characters on the screen
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
** Initializes the tty driver
*/
static void
tty_init(enum init_level il __unused)
{
	struct io_output_callbacks cb;

	cb.putc = tty_putchar;
	cb.puts = tty_puts;
	tty.vgabuff = TTY_BUFFER;
	tty_set_color(TTY_LIGHT_PINK, TTY_BLACK);
	tty_clear();
	register_io_output_callbacks(&cb, IO_OUTPUT_CONSOLE);
}

NEW_DRIVER_HOOK(tty_init, &tty_init, CHAOS_INIT_LEVEL_DRIVER_EARLY);
