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
		++s;
	}
	return ((size_t)(s - str));
}

void *
memset(void *src, int c, size_t n)
{
	unsigned char *s;

	s = src;
	while (n)
	{
		*s++ = c;
		--n;
	}
	return (src);
}

void *
memcpy(void *dest, void const *src, size_t n)
{
	unsigned char *d;
	unsigned char const *s;

	s = src;
	d = dest;
	while (n)
	{
		*d++ = *s++;
		--n;
	}
	return (dest);
}

int
memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char const *c1;
	unsigned char const *c2;

	c1 = s1;
	c2 = s2;
	while (n)
	{
		if (*c1 != *c2) {
			return (*c1 - *c2);
		}
		++c1;
		++c2;
		--n;
	}
	return (0);
}

void *
memchr(void const *src, int c, size_t n)
{
	unsigned char const *s;

	s = src;
	while (n)
	{
		if (*s == c) {
			return ((void *)s);
		}
		++s;
		--n;
	}
	return (NULL);
}
