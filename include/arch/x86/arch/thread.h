/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ARCH_X86_ARCH_THREAD_H_
# define _ARCH_X86_ARCH_THREAD_H_

struct		arch_thread
{
	virt_addr_t sp;
};

struct		context_switch_frame
{
	uintptr edi;
	uintptr esi;
	uintptr ebp;
	uintptr esp;
	uintptr ebx;
	uintptr edx;
	uintptr ecx;
	uintptr eax;
	uintptr eflags;
	uintptr eip;
};

extern void 	x86_context_switch(void **old_esp, void *new_esp);

#endif /* _ARCH_X86_ARCH_THREAD_H_ */
