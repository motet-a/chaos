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

/*
** An entry in the page directory
*/
struct			pagedir_entry
{
	union
	{
		struct
		{
			uint32 present : 1;	/* Present in memory */
			uint32 rw : 1;		/* 0 => Readonly / 1 => Readwrite */
			uint32 user : 1;	/* 0 => Kernel page / 1 => User */
			uint32 wtrough : 1;	/* 1 => write through caching */
			uint32 cache : 1;	/* 1 => Cache disable */
			uint32 accessed : 1;	/* set by cpu when accessed */
			uint32 _zero : 1;	/* Must be 0 */
			uint32 size : 1;	/* 0 => 4KiB page, 1 => 4MiB page */
			uint32 __unusued : 4;	/* unused & reserved bits */
			uint32 frame : 20;	/* Frame address */
		};
		uintptr value;
	};
};

/*
** An entry in a page table
*/
struct			pagetable_entry
{
	union
	{
		struct
		{
			uint32 present : 1;	/* Present in memory */
			uint32 rw : 1;		/* 0 => Readonly / 1 => Readwrite */
			uint32 user : 1;	/* 0 => Kernel page / 1 => User */
			uint32 wtrough : 1;	/* 1 => write through caching */
			uint32 cache : 1;	/* 1 => Cache disable */
			uint32 accessed : 1;	/* set by cpu when accessed */
			uint32 dirty : 1;	/* Set by cpu when writting */
			uint32 _zero : 1;	/* Must be zero */
			uint32 global : 1;	/* Prevent tlb update */
			uint32 __unusued : 3;	/* unused & reserved bits */
			uint32 frame : 20;	/* Frame address */
		} __packed;
		uintptr value;
	};
};

void			vmm_init(void);

#endif /* !_KERNEL_VMM_H_ */