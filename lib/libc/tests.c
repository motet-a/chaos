/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/unit-tests.h>
#include <debug.h>
#include <string.h>

static void
strcmp_tests(void)
{
	assert_eq(strcmp("", ""), 0);
	assert_gr(strcmp("a", ""), 0);
	assert_lo(strcmp("", "a"), 0);
	assert_eq(strcmp("aze", "aze"), 0);
	assert_lo(strcmp("lolilo", "lolilol"), 0);
	assert_gr(strcmp("brqz", "brq"), 0);
	assert_gr(strcmp("kek", "kak"), 0);
	assert_lo(strcmp("azerty", "qwerty"), 0);
	assert_lo(strcmp("qwerty", "qwertz"), 0);
}

static void
strncmp_tests(void)
{
	assert_eq(strncmp(NULL, NULL, 0), 0);
	assert_eq(strncmp("", "", 0), 0);
	assert_eq(strncmp("", "", -1), 0);
	assert_eq(strncmp("", "", 1), 0);
	assert_eq(strncmp("", "", 10), 0);
	assert_eq(strncmp("a", "", 0), 0);
	assert_gr(strncmp("a", "", 1), 0);
	assert_gr(strncmp("a", "", 2), 0);
	assert_eq(strncmp("", "a", 0), 0);
	assert_lo(strncmp("", "a", 1), 0);
	assert_lo(strncmp("", "a", 2), 0);
	assert_eq(strncmp("aze", "aze", 0), 0);
	assert_eq(strncmp("aze", "aze", 1), 0);
	assert_eq(strncmp("aze", "aze", 2), 0);
	assert_eq(strncmp("aze", "aze", 3), 0);
	assert_eq(strncmp("aze", "aze", 4), 0);
	assert_eq(strncmp("aze", "aze", 5), 0);
	assert_eq(strncmp("lolilo", "lolilol", 1), 0);
	assert_eq(strncmp("lolilo", "lolilol", 2), 0);
	assert_eq(strncmp("lolilo", "lolilol", 3), 0);
	assert_eq(strncmp("lolilo", "lolilol", 6), 0);
	assert_lo(strncmp("lolilo", "lolilol", 7), 0);
	assert_lo(strncmp("lolilo", "lolilol", 8), 0);
	assert_eq(strncmp("brqz", "brq", 1), 0);
	assert_eq(strncmp("brqz", "brq", 2), 0);
	assert_eq(strncmp("brqz", "brq", 3), 0);
	assert_gr(strncmp("brqz", "brq", 4), 0);
	assert_gr(strncmp("brqz", "brq", 5), 0);
	assert_eq(strncmp("kek", "kak", 1), 0);
	assert_gr(strncmp("kek", "kak", 2), 0);
	assert_lo(strncmp("kak", "kek", 2), 0);
	assert_gr(strncmp("kek", "kak", 3), 0);
	assert_gr(strncmp("kek", "kak", 4), 0);
	assert_gr(strncmp("kek", "kak", 5), 0);
	assert_eq(strncmp("azerty", "qwerty", 0), 0);
	assert_lo(strncmp("azerty", "qwerty", 1), 0);
	assert_lo(strncmp("azerty", "qwerty", 2), 0);
	assert_eq(strncmp("qwerty", "qwertz", 1), 0);
	assert_eq(strncmp("qwerty", "qwertz", 2), 0);
	assert_eq(strncmp("qwerty", "qwertz", 3), 0);
	assert_eq(strncmp("qwerty", "qwertz", 5), 0);
	assert_lo(strncmp("qwerty", "qwertz", 6), 0);
	assert_lo(strncmp("qwerty", "qwertz", 7), 0);
}

static void
strstr_tests(void)
{
	char *a;
	char *b;
	char *c;
	char *d;
	char *e;

	a = "azerty";
	b = "qwerty";
	c = "qwertz";
	d = "azaze";
	e = "";
	assert_eq(strstr(a, b + 3), a + 3);
	assert_eq(strstr(a, c), NULL);
	assert_eq(strstr(a, "z"), a + 1);
	assert_eq(strstr(a, "ze"), a + 1);
	assert_eq(strstr(a, a), a);
	assert_eq(strstr(a, a + 1), a + 1);
	assert_eq(strstr(a, "azoekazopekazpekapekazoeaz"), NULL);
	assert_eq(strstr(a, "azertyuiop"), NULL);
	assert_eq(strstr(a, "azerf"), NULL);
	assert_eq(strstr("azerty", "azaze"), NULL);
	assert_eq(strstr(a, "a"), a);
	assert_eq(strstr(a, "p"), NULL);
	assert_eq(strstr(d, "aze"), d + 2);
	assert_eq(strstr(d, "az"), d);
	assert_eq(strstr(e, e), e);
	assert_eq(strstr(e, "a"), NULL);
	assert_eq(strstr(a, e), a);
}

static void
libc_tests(void)
{
	strcmp_tests();
	strncmp_tests();
	strstr_tests();
}

NEW_UNIT_TEST(libc, &libc_tests, UNIT_TEST_LEVEL_NORMAL);
