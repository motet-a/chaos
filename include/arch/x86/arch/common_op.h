/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ARCH_X86_ARCH_COMMON_OP_H_
# define _ARCH_X86_ARCH_COMMON_OP_H_

static inline uint
atomic_exchange(volatile uint *addr, uint newval)
{
	asm volatile("xchgl %[newval], %[addr];"
			: [newval]"=a" (newval)
			: "a" (newval), [addr]"m" (*addr)
			: "memory");
	return newval;
}



#endif /* !_ARCH_X86_ARCH_COMMON_OP_H_ */
