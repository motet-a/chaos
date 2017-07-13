/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <lib/interrupts.h>
#include <chaosdef.h>
#include <stdio.h>

/*
** Make the kernel panic with the given error message.
** Never returns.
*/
void
panic(const char *fmt, ...)
{
	va_list va;

	disable_interrupts();
	va_start(va, fmt);
	printf("\nKernel panicked: ");
	vprintf(fmt, va);
	va_end(va);
	for (;;)
		;
}

