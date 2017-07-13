/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/linker.h>
#include <kernel/init.h>
#include <platform/pc/vga.h>
#include <lib/io.h>
#include <string.h>

/* Global definitions */
static struct vga vga;
static uint const	VGA_WIDTH	= 80;
static uint const	VGA_HEIGHT	= 25;
static uint16 *const	VGA_BUFFER	= (uint16*)((char *)KERNEL_VIRTUAL_BASE + 0xB8000);

/*
** Sets the current color for next outputs
*/
void
vga_set_color(enum VGA_COLOR fg, enum VGA_COLOR bg)
{
	vga.vga_attrib = ((bg << 4u) | (fg & 0x0F)) << 8u;
}

/*
** Clears the screen
*/
void
vga_clear(void)
{
	uint i;
	uint16 blank;

	i = 0;
	blank = vga.vga_attrib | 0x20;
	while (i < VGA_WIDTH)
	{
		*(vga.vgabuff + i) = blank;
		++i;
	}
	i = 1;
	while (i < VGA_HEIGHT)
	{
		memcpy(vga.vgabuff + VGA_WIDTH * i, vga.vgabuff, sizeof(uint16) * VGA_WIDTH);
		++i;
	}
}

/*
** Scrolls the text
*/
static void
vga_scroll(void)
{
	uint16 blank;
	size_t i = 0;

	i = 0;
	blank = vga.vga_attrib | 0x20;
	memmove(vga.vgabuff, vga.vgabuff + VGA_WIDTH, (VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(uint16));
	while (i < VGA_WIDTH)
	{
		*(vga.vgabuff + (VGA_HEIGHT - 1) * VGA_WIDTH + i) = blank;
		++i;
	}
}

/*
** Prints a single character on the screen
*/
static int
vga_putchar(int c)
{
	switch (c)
	{
	case '\n': /* new line */
		vga.cursor_x = 0;
		vga.cursor_y++;
		break;
	case '\t':
		vga.cursor_x = (vga.cursor_x + 8u) & ~7u;
		break;
	case '\r':
		vga.cursor_x = 0;
		break;
	default:
		*(vga.vgabuff + vga.cursor_y * VGA_WIDTH + vga.cursor_x) =
			vga.vga_attrib | (uchar)c;
		vga.cursor_x += 1;
		break;
	}
	vga.cursor_y += (vga.cursor_x >= VGA_WIDTH);
	vga.cursor_x *= (vga.cursor_x < VGA_WIDTH);
	while (vga.cursor_y >= VGA_HEIGHT) {
		vga_scroll();
		vga.cursor_y -= 1;
	}
	return (1);
}

/*
** Prints an array of characters on the screen
*/
static int
vga_puts(char const *str)
{
	char const *s;

	s = str;
	while (*str) {
		vga_putchar(*str);
		++str;
	}
	return (str - s);
}

/*
** Initializes the vga driver
*/
static void
vga_init(enum init_level il __unused)
{
	struct io_output_callbacks cb;

	cb.putc = vga_putchar;
	cb.puts = vga_puts;
	vga.vgabuff = VGA_BUFFER;
	vga_set_color(VGA_LIGHT_PINK, VGA_BLACK);
	vga_clear();
	register_io_output_callbacks(&cb, IO_OUTPUT_CONSOLE);
}

NEW_INIT_HOOK(vga_init, &vga_init, CHAOS_INIT_LEVEL_PLATFORM_EARLY);
