/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _PLATFORM_PC_VGA_H_
# define _PLATFORM_PC_VGA_H_

# include <chaosdef.h>
# include <kernel/spinlock.h>

/*
** All the colors that the vga mode can handle
*/
enum			VGA_COLOR
{
	VGA_BLACK	= 0,
	VGA_BLUE	= 1,
	VGA_GREEN	= 2,
	VGA_CYAN	= 3,
	VGA_RED		= 4,
	VGA_PINK	= 5,
	VGA_BROWN	= 6,
	VGA_LIGHT_GREY	= 7,
	VGA_DARK_GREY	= 8,
	VGA_LIGHT_BLUE	= 9,
	VGA_LIGHT_GREEN	= 10,
	VGA_LIGHT_CYAN	= 11,
	VGA_LIGHT_RED	= 12,
	VGA_LIGHT_PINK	= 13,
	VGA_YELLOW	= 14,
	VGA_WHITE	= 15
};

struct			vga
{
	struct spinlock	lock;
	uint16		vga_attrib;
	uint16		*vgabuff;
	uint		cursor_x;
	uint		cursor_y;
};

void			vga_set_color(enum VGA_COLOR, enum VGA_COLOR);
void			vga_clear(void);

#endif /* !_PLATFORM_PC_VGA_H_ */
