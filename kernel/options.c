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

static struct options options = {0};

static struct options
parse_command_line(char const *string)
{
	printf("Multiboot command line: %s\n", string);

	return ((struct options){
		.test = strstr(string, "test"),
	});
}

void
options_parse_command_line(char const *string)
{
	options = parse_command_line(string);
}

struct options
get_options(void) {
	return (options);
}
