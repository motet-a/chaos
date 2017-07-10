/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _DEV_GDT_H_
# define _DEV_GDT_H_

# include <chaosdef.h>
# include <asm.h>

struct		gdt_entry
{
	uint16 limit_low;
	uint16 base_low;
	uint8 base_middle;
	uint8 access;
	uint8 limit_high : 4;
	uint8 flags: 4;
	uint8 base_high;
} __packed;

/*
** The GDT_ENTRY() macro generates a gdt entry depending on the
** flags given as parameter.
*/
# define	GDT_ENTRY(fl, base, limit)			\
	{							\
		.limit_low =   (limit) & 0x0000FFFFUL,		\
		.base_low =     (base) & 0x0000FFFFUL,		\
		.base_middle = ((base) & 0x00FF0000UL) >> 16u,	\
		.access =      (fl) & 0x000000FFUL,		\
		.limit_high = ((limit) & 0x000F0000UL) >> 16u,	\
		.flags =      ((fl) & 0x0000F000UL) >> 12u,	\
		.base_high =   ((base) & 0xFF000000UL) >> 24u	\
	}							\

enum		gdt_entries
{
	GDT_NULL_ENTRY		= 0,
	GDT_KERNEL_CODE		= 1,
	GDT_KERNEL_DATA		= 2,
	GDT_USER_CODE		= 3,
	GDT_USER_DATA		= 4,

	GDT_SIZE		= 5,
};

void		gdt_flush(struct table_desc_ptr *);

#endif /* !_DEV_GDT_H_ */
