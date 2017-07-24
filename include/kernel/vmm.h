/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _KERNEL_VMM_H_
# define _KERNEL_VMM_H_

# include <kernel/pmm.h>
# include <arch/vaspace.h>
# include <chaosdef.h>
# include <chaoserr.h>

typedef void 		*virt_addr_t;

/*
** Represents the virtual address space of a process.
*/
struct vaspace
{
	uintptr data_start;
	uintptr data_pos;
	size_t data_size;

	uintptr stack_start;
	size_t stack_size;

	struct arch_vaspace arch;
};

status_t		map_virt_to_phys();
status_t		map_page(virt_addr_t va);
virt_addr_t		mmap(virt_addr_t va, size_t size);
void			munmap(virt_addr_t va, size_t size);
status_t		kbrk(virt_addr_t new_brk);
virt_addr_t		ksbrk(intptr);

#endif /* !_KERNEL_VMM_H_ */
