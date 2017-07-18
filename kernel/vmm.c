/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

/*
** Architecture independant virtual memory management.
**
** TODO:
**	- Support arch-independant flags for page entries
**	- Support pages of different size.
*/

#include <kernel/init.h>
#include <kernel/unit-tests.h>
#include <kernel/vmm.h>
#include <stdio.h>

/*
** Maps a physical address to a virtual one.
**
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak status_t
map_virt_to_phys(virt_addr_t va __unused, phys_addr_t pa __unused)
{
	return (ERR_NOT_IMPLEMENTED);
}

/*
** Maps random physical addresses to the given virtual address.
**
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak status_t
map_page(virt_addr_t va __unused)
{
	return (ERR_NOT_IMPLEMENTED);
}

/*
** Unmaps a virtual address.
**
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak void
munmap(virt_addr_t va __unused, size_t s __unused)
{}

/*
** Map contiguous virtual addresses to a random physical addresses.
** In case of error, the state mush be as it was before the call.
** If the given virtual address is NULL, then the kernel chooses
** the destination address.
** Size must be page aligned.
**
** Returns the virtual address holding the mapping, or NULL if
** it fails.
**
** Weak symbol, can be re-implemented for each supported architecture, but
** a default implemententation is given.
*/
__weak virt_addr_t
mmap(virt_addr_t va, size_t size)
{
	virt_addr_t ori_va;

	assert(IS_PAGE_ALIGNED(va));
	assert(IS_PAGE_ALIGNED(size));
	ori_va = va;
	if (va == NULL) /* Random virtual address */
	{
		panic("NULL mmap() not implemented (yet)!");
	}
	else
	{
		while (va < ori_va + size)
		{
			if (unlikely(map_page(va) != OK)) {
				munmap(ori_va, va - ori_va);
				return (NULL);
			}
			va += PAGE_SIZE;
		}
		return (ori_va);
	}
	return (NULL);
}

/*
** Initialises the arch-dependent stuff of virtual memory management.
**
** Weak symbol, should be re-implemented for each supported architecture.
*/
__weak void
arch_vmm_init(void)
{}

/*
** Initalises the arch-independant stuff of virtual memory management.
** Calls the arch-dependent vmm init function.
*/
static void
vmm_init(enum init_level il __unused)
{
	arch_vmm_init();
	printf("[OK]\tVirtual Memory Management\n");
}

__weak void
vmm_test(void)
{}

NEW_INIT_HOOK(vmm, &vmm_init, CHAOS_INIT_LEVEL_VMM);
NEW_UNIT_TEST(vmm, &vmm_test, UNIT_TEST_LEVEL_MEMORY);
