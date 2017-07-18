/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _KERNEL_THREAD_H_
# define _KERNEL_THREAD_H_

# include <chaosdef.h>
# include <arch/thread.h>

struct thread
{
	char name[255];

	/* Thread stack */
	void *stack;
	size_t stack_size;

	struct arch_thread arch;
};

#endif /* !_KERNEL_THREAD_H_ */
