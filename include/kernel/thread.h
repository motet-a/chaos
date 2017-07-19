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

enum thread_state
{
	SUSPENDED = 0,
	RUNNABLE,
	RUNNING,
	ZOMBIE,
};

struct thread
{
	char name[255];

	/* Thread stack */
	void *stack;
	size_t stack_size;

	/* arch stuff */
	struct arch_thread arch;

	/* Current state */
	enum thread_state state;
};

void		thread_init(void);
void		thread_become_idle(void);
void		thread_yield(void);
void		thread_dump(void);

/* Must be implemented in each architecture */
void		set_current_thread(struct thread *);
struct thread	*get_current_thread(void);

#endif /* !_KERNEL_THREAD_H_ */
