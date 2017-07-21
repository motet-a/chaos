/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <kernel/thread.h>
#include <lib/interrupts.h>
#include <stdio.h>
#include <string.h>

/* Next pid available */
static pid_t next_pid = 1;

/* Thread table */
struct thread thread_table[MAX_PID];
struct thread *idle_thread = thread_table;

extern void * stack_a;
extern void * stack_b;
extern void * stack_c;

void *stacks[] =
{
	&stack_a,
	&stack_b,
	&stack_c,
};

/* String to print thread state */
static char const *thread_state_str[] =
{
	[NONE]		= "NONE",
	[SUSPENDED]	= "SUSPENDED",
	[RUNNABLE]	= "RUNNABLE",
	[RUNNING]	= "RUNNING",
	[ZOMBIE]	= "ZOMBIE",
};

/*
** Look for the next available pid.
** Returns -1 if no pid are available.
**
** TODO This function is unsafe and uncomplete right now.
*/
static pid_t
find_next_pid()
{
	return (next_pid++);
}

/*
** Sets the name of the given thread.
*/
static void
thread_set_name(struct thread *t, char const *name)
{
	strncpy(t->name, name, sizeof(t->name) - 1);
	t->name[sizeof(t->name) - 1] = '\0';
}

/*
** Creates a new thread.
** The newly created thread is in a suspended state,
** so it should be resumed with thread_resume().
**
** Returns NULL if the thread couldn't be created.
*/
struct thread *
thread_create(char const *name, thread_entry_cb entry, size_t stack_size)
{
	struct thread *t;
	pid_t pid;

	pid = find_next_pid();
	if (unlikely(pid == -1)) {
		return (NULL);
	}

	t = thread_table + pid;
	memset(t, 0, sizeof(*t));
	thread_set_name(t, name);
	t->pid = pid;
	t->stack_size = stack_size;
	t->entry = entry;
	t->state = SUSPENDED;

	/* TODO set thread stack */
	t->stack = stacks[pid - 1]; /* Quick hack, will be removed later */

	arch_init_thread(t);
	return (t);
}

/*
** The routine executed when the cpu has nothing to do.
** This routine can be used to do background stuff, like
** zero-ing pages.
*/
static void
idle_thread_routine(void)
{
	uintmax i;

	while (42) {
		i = 0;
		/*
		** Horrible way (but still not as much as you) to delay the output.
		** This is of course here only for debugging purposes,
		** so please stop yelling everywhere. Thanks.
		** FIXME
		*/
		while(i++ < 1000000)
			printf("");
		thread_dump();
	}
}

/*
** Mark the current thread as the idle thread.
*/
void
thread_become_idle(void)
{
	assert(!are_int_enabled());

	/* Set the thread name to 'idle' */
	thread_set_name(get_current_thread(), "idle");

	/* Enable interrupts */
	enable_interrupts();

	/* Yield the cpu to an other thread */
	thread_yield();

	/* Do the idle routine */
	idle_thread_routine();
}

/*
** Put us in some sort of thread context.
** Called from kmain.
*/
void
thread_init(void)
{
	struct thread *t;

	t = idle_thread;

	memset(thread_table, 0, sizeof(thread_table));
	thread_set_name(t, "boot");
	t->state = RUNNING;
	set_current_thread(t);
	register_int_handler(IRQ_TIMER_VECTOR, &irq_timer_handler);
}

/*
** Thread dumper to help debug.
*/
void
thread_dump(void)
{
	struct thread *t;

	t = thread_table;
	printf("\n");
	while (t < thread_table + MAX_PID)
	{
		if (t->state != NONE) {
			printf("%i:[%s] - [%s]\n", t->pid, t->name, thread_state_str[t->state]);
		}
		++t;
	}
}
