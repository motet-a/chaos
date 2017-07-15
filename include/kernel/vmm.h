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
void			vmm_init(void);

#endif /* !_KERNEL_VMM_H_ */
