/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <kernel/pmm.h>
#include <stdio.h>

/*
** Common entry point of the kernel.
*/
int
kernel_main()
{
	kernel_init_level(CHAOS_INIT_LEVEL_EARLIEST, CHAOS_INIT_LEVEL_LATEST);
	pmm_init();
	printf("\nWelcome to ChaOS\n\n");
	return (0);
}
