/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ASM_H_
# define _ASM_H_

# include <chaosdef.h>

static inline void
outb(ushort port, uchar data)
{
	asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline uchar
inb(ushort port)
{
	uchar data;

	asm volatile("in %1, %0" : "=a"(data) : "d" (port));
	return (data);
}

static inline void
interrupt(uchar i)
{
	asm volatile("int %0" :: "i" (i));
}

#endif /* !_ASM_H_ */
