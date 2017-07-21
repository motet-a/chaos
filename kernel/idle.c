/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/thread.h>
#include <lib/interrupts.h>
#include <stdio.h>

/*
** The routine executed when the cpu has nothing to do.
** This routine can be used to do background stuff, like
** zero-ing pages.
*/
void
idle_routine(void)
{
	uintmax i;

	while (42) {
		i = 0;
		/*
		** Horrible way (but still not as much as you) to delay the output.
		** This is of course here only for debugging purposes,
		** so please stop yelling everywhere. Thanks.
		** FIXME
		*/
		while(i++ < 1000000)
			assert(are_int_enabled());
		thread_dump();
	}
}

