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

# include <chaosdef.h>
# include <chaoserr.h>
# include <kernel/pmm.h>

typedef void 		*virt_addr_t;

status_t		arch_map_virt_to_phys();
status_t		arch_map_page(virt_addr_t va __unused);
status_t		arch_mmap(virt_addr_t va __unused, size_t size __unused);
status_t		arch_munmap(virt_addr_t va __unused);

#endif /* !_KERNEL_VMM_H_ */
