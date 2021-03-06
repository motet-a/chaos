/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/options.h>
#include <string.h>
#include <stdio.h>

static struct options options;

void
options_parse_command_line(char const *string)
{
	options.unit_test = strstr(string, "--unit-test") != NULL;
}

bool
options_is_unit_tests_enabled(void)
{
	return (options.unit_test);
}
