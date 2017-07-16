/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <string.h>

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

int
strcmp(char const *s1, char const *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0') {
			return (0);
		}
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int
strncmp(char const *s1, char const *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2 || *s1 == '\0')
			return (*s1 - *s2);
		++s1;
		++s2;
		--n;
	}
	return (0);
}

char
*strstr(char const *haystack, char const *needle)
{
	size_t len;
	char sc;
	char c;

	c = *needle++;
	len = strlen(needle);
	if (c == '\0') {
		return ((char *)haystack);
	}
	do
	{
		do
		{
			sc = *haystack++;
			if (sc == '\0') {
				return (NULL);
			}
		}
		while (sc != c);
	}
	while (strncmp(haystack, needle, len) != 0);
	return ((char *)haystack - 1);
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

void *
memmove(void *dest, void const *src, size_t n)
{
	unsigned char *d;
	unsigned char const *s;

	s = src;
	d = dest;
	if (s > d) {
		while (n-- > 0)
			*d++ = *s++;
	}
	else {
		while (n-- > 0)
			d[n] = s[n];
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
