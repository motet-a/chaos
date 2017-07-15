/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <arch/x86/vmm.h>
#include <stdio.h>

/*
** Maps a physical address to a virtual one.
** Returns the page table entry containing the virtual address on success,
** NULL otherwise.
*/
static struct page_table_entry *
x86_map_virt_to_phys(virt_addr_t va __unused, phys_addr_t pa __unused)
{
	return (NULL);
}

status_t
arch_map_virt_to_phys(virt_addr_t va, phys_addr_t pa)
{
	return (x86_map_virt_to_phys(va, pa) == NULL ? ERR_NO_MEMORY : OK);
}

status_t
arch_unmap_vaddress(virt_addr_t va __unused)
{
	return (OK);
}

void
arch_vmm_init(void)
{
}
