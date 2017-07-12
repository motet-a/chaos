/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <drivers/tty.h>
#include <stdio.h>

#include <arch/x86/asm.h>
#include <lib/interrupts.h>

/*
** Common entry point of the kernel.
*/
int
main()
{
	kernel_init_level(CHAOS_INIT_LEVEL_EARLIEST, CHAOS_INIT_LEVEL_LATEST);
	printf("Welcome to ChaOS\n");
	return (0);
}
