/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ARCH_X86_X86_H_
# define _ARCH_X86_X86_H_

# include <chaosdef.h>

/* These must match with gdt.asm and include/arch/x86/segments.h */
#define		CODE_SELECTOR		(0x08)
#define		KERNEL_DATA_SELECTOR	(0x10)
#define		USER_DATA_SELECTOR	(0x18)

/*
** This structure represents the registers and all other informations that
** each interrupt handler receives when triggered.
*/
struct		regs
{
		uintptr gs;
		uintptr fs;
		uintptr es;
		uintptr ds;
		uintptr edi;
		uintptr esi;
		uintptr ebp;
		uintptr _popa_esp;
		uintptr ebx;
		uintptr edx;
		uintptr ecx;
		uintptr eax;
		uintptr int_num;
		uintptr err_code;
		uintptr eip;
		uintptr cs;
		uintptr eflags;
		uintptr esp;
		uintptr ss;
};

/*
** An enumeration of all rings level
*/
enum			dpl
{
	DPL_RING_0	= 0,
	DPL_RING_1	= 1,
	DPL_RING_2	= 2,
	DPL_RING_3	= 3,
};

#endif /* !_ARCH_X86_X86_H_ */
