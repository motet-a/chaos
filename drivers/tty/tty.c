/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/linker.h>
#include <drivers/tty.h>

/* Global definitions */
static struct tty tty;
static uint const	TTY_WIDTH	= 80;
static uint const	TTY_HEIGHT	= 80;
static uint16 *const	TTY_BUFFER	= (uint16*)((char *)KERNEL_VIRTUAL_BASE + 0xB8000);

/*
** Initialize the tty driver
*/
void
tty_init(void)
{
	tty.vgabuff = TTY_BUFFER;
	tty_set_color(TTY_WHITE, TTY_DARK_GREY);
	tty_clear();
}

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
void
tty_putchar(char c)
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
		tty.cursor_y -= 1;
	}
}

/*
** Print an array of character on the screen
*/
void
tty_puts(char const *str)
{
	while (*str) {
		tty_putchar(*str);
		++str;
	}
}
