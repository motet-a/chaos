/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ARCH_X86_ASM_H_
# define _ARCH_X86_ASM_H_

# include <chaosdef.h>

static inline void
cli(void)
{
  asm volatile("cli");
}

static inline void
sti(void)
{
  asm volatile("sti");
}

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

static inline uintptr
get_eflags(void)
{
	uintptr eflags;

	asm volatile("pushfl; popl %0" : "=r" (eflags));
	return (eflags);
}

static inline void
set_eflags(uintptr eflags)
{
	asm volatile("pushl %0; popfl" :: "r" (eflags));
}

static inline uintptr
get_cr2(void)
{
	uintptr cr2;

	asm volatile("mov %%cr2, %0" : "=r"(cr2));
	return (cr2);
}

static inline void
interrupt(uchar i)
{
	asm volatile("int %0" :: "i" (i));
}

static inline void
invlpg(void *va)
{
	asm volatile("invlpg (%0)" ::"r" (va) : "memory");
}

#endif /* !_ARCH_X86_ASM_H_ */
