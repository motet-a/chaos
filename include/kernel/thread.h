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

# include <kernel/vmm.h>
# include <arch/thread.h>
# include <chaosdef.h>

/* Maximum number of threads */
# define MAX_PID		(32u)
# define DEFAULT_STACK_SIZE	(0x1000 * 16u)

# define IRQ_TIMER_VECTOR	(0x0)

typedef int			pid_t;
typedef void			(*thread_entry_cb)(void);

enum			thread_state
{
	NONE = 0,
	SUSPENDED,
	RUNNABLE,
	RUNNING,
	ZOMBIE,
};

struct			thread
{
	/* Thread basic infos*/
	char name[255];
	pid_t pid;
	enum thread_state state;

	/* Thread stack */
	virt_addr_t stack;
	size_t stack_size;

	/* arch stuff */
	struct arch_thread arch;

	/* entry point */
	thread_entry_cb entry;

	/* TODO add memory space of thread */
};

struct thread		*thread_create(char const *name, thread_entry_cb entry, size_t stack_size);
void			thread_init(void);
void			thread_become_idle(void);
void			thread_dump(void);
void			thread_yield(void);
void			thread_resume(struct thread *);
enum handler_return	irq_timer_handler(void);
void			idle_routine(void);

/* Must be implemented in each architecture */
void			set_current_thread(struct thread *);
struct thread		*get_current_thread(void);
void			arch_context_switch(struct thread *old, struct thread *new);
void			arch_init_thread(struct thread *);

#endif /* !_KERNEL_THREAD_H_ */
