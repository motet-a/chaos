/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ARCH_X86_ARCH_VASPACE_H_
# define _ARCH_X86_ARCH_VASPACE_H_

# include <kernel/pmm.h>

struct arch_vaspace
{
	phys_addr_t pagedir;
};

#endif /* !_ARCH_X86_ARCH_VASPACE_H_ */
