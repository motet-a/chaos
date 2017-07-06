/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _TTY_H_
# define _TTY_H_

# include "chaosdef.h"

/****************************************************************************\
**
** Type definition
**
\****************************************************************************/

enum			TTY_COLOR
{
	TTY_BLACK	= 0,
	TTY_BLUE	= 1,
	TTY_GREEN	= 2,
	TTY_CYAN	= 3,
	TTY_RED		= 4,
	TTY_PINK	= 5,
	TTY_BROWN	= 6,
	TTY_LIGHT_GREY	= 7,
	TTY_DARK_GREY	= 8,
	TTY_LIGHT_BLUE	= 9,
	TTY_LIGHT_GREEN	= 10,
	TTY_LIGHT_CYAN	= 11,
	TTY_LIGHT_RED	= 12,
	TTY_LIGHT_PINK	= 13,
	TTY_YELLOW	= 14,
	TTY_WHITE	= 15
};

struct			tty
{
	uint16		vga_attrib;
	uint16		*vgabuff;
	uint		cursor_x;
	uint		cursor_y;
};

/****************************************************************************\
**
** Global variables
**
\****************************************************************************/

struct tty		tty;

/****************************************************************************\
**
** Function prototypes
**
\****************************************************************************/

void			tty_init(void);
void			tty_set_color(enum TTY_COLOR, enum TTY_COLOR);
void			tty_clear(void);
void			tty_putchar(char);
void			tty_puts(char const *);

#endif // !_TTY_H_
