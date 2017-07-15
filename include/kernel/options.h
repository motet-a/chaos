/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _KERNEL_OPTIONS_H_
# define _KERNEL_OPTIONS_H_

#include <stdbool.h>

struct options {
	bool test;
};

void		options_parse_command_line(char const *string);
struct options	get_options(void);

#endif /* !_KERNEL_OPTIONS_H_ */
