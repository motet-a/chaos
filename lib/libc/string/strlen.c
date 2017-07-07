/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <stddef.h>

size_t
strlen(char const *str)
{
	char const *s;

	s = str;
	while (*s) {
		s++;
	}
	return ((size_t)(s - str));
}
