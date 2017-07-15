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

static bool
starts_with(char const *string, char const *prefix)
{
	while (*string && *string == *prefix) {
		++string;
		++prefix;
	}
	return (!*prefix);
}

static void
starts_with_test(void)
{
	assert(starts_with("", ""));
	assert(!starts_with("", "a"));
	assert(starts_with("a", ""));
	assert(starts_with("a", "a"));
	assert(starts_with("boat", "boa"));
	assert(starts_with("boat", "boat"));
	assert(!starts_with(" boat", "boat"));
}

char
*strstr(char const *haystack, char const *needle)
{
	while (true) {
		if (starts_with(haystack, needle)) {
			return (char *)haystack;
		}
		if (!*haystack) {
			return (NULL);
		}
		++haystack;
	}
}

static ptrdiff_t
strstr_index(char const *haystack, char const *needle)
{
	char const *result = strstr(haystack, needle);
	if (!result) {
		return (-1);
	}
	assert(result >= haystack);
	if (strlen(haystack)) {
		assert(result < haystack + strlen(haystack));
	}
	return (result - haystack);
}

static void
strstr_test(void)
{
	assert(strstr_index("", "") == 0);
	assert(strstr_index("a", "") == 0);
	assert(strstr_index("a", "a") == 0);
	assert(strstr_index("ba", "a") == 1);
	assert(strstr_index("", "a") == -1);
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

void
string_test(void)
{
	starts_with_test();
	strstr_test();
}
