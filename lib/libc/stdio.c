/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <stdio.h>
#include <lib/io.h>

int
puts(char const *str)
{
	io_puts(str);
	return (1);
}

int
putc(int c)
{
	io_putc(c);
	return ((int)(unsigned char)c);
}
