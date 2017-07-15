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
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak void
arch_vmm_init(void)
{}

/*
** Maps a physical address to a virtual one.
**
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak status_t
arch_map_virt_to_phys(virt_addr_t va __unused, phys_addr_t pa __unused)
{
	return (ERR_NOT_IMPLEMENTED);
}

/*
** Unmaps a virtual address.
**
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak status_t
arch_unmap_vaddress(virt_addr_t va __unused)
{
	return (ERR_NOT_IMPLEMENTED);
}

/*
** Initalises the arch-independant stuff of virtual memory management.
** Calls the arch-dependent vmm init function.
*/
void
vmm_init(void)
{
	arch_vmm_init();
	printf("[OK]\tVirtual Memory Management\n");
}
