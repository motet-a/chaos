/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _KERNEL_PMM_H_
# define _KERNEL_PMM_H_

# include <chaosdef.h>
# include <kernel/linker.h>
# include <limits.h>

/* A physical address */
typedef uintptr			phys_addr_t;

/* The NULL equivalent for physical memory */
# define NULL_FRAME		(-1u)

/* The number of frames */
# define NB_FRAMES		((UINTPTR_MAX / PAGE_SIZE) + 1)

/* *The number of cells of the frame bitmap */
# define FRAME_BITMAP_SIZE	(NB_FRAMES / 8u)

/* Macro to easily get the index in the bitmap of any physical address */
# define GET_FRAME_IDX(x)		(((x) >> 12u) / 8u)
# define GET_FRAME_MASK(x)		(1 << (((x) >> 12) % 8u))

/* Physical allocation functions */
phys_addr_t			alloc_frame(void);
void				free_frame(phys_addr_t);

/* Physical Memory Manager init */
void				pmm_init(void);
void				pmm_unit_tests(void);


#endif /* !_KERNEL_PMM_H_ */
