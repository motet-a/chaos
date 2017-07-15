/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/vmm.h>
#include <stdio.h>

/*
** Initialises the arch-dependent stuff of virtual memory management.
**
** Weak symbol, should be re-implemented on each architecture.
*/
__weak void
arch_vmm_init(void)
{}

/*
** Initalises the arch-independant stuff of virtual memory management.
*/
void
vmm_init(void)
{
	arch_vmm_init();
	printf("[OK]\tVirtual Memory Management\n");
}
