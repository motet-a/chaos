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

/* Idle thread, the one runs when there is nothing else to do */
static struct thread idle_thread;

/* String to print thread state */
static char const *thread_state_str[] =
{
	[SUSPENDED] = "SUSPENDED",
	[RUNNABLE] = "RUNNABLE",
	[RUNNING] = "RUNNING",
	[ZOMBIE] = "ZOMBIE",
};

/*
** Initializes the thread structure.
*/
static void
thread_init_struct(struct thread *t, const char *name)
{
	memset(t, 0, sizeof(*t));
	strncpy(t->name, name, sizeof(t->name) - 1);
	t->name[sizeof(t->name) - 1] = '\0';
}

/*
** Sets the name of the thread.
*/
static void
thread_set_name(char const *name)
{
	struct thread *t;

	t = get_current_thread();
	strncpy(t->name, name, sizeof(t->name) - 1);
	t->name[sizeof(t->name) - 1] = '\0';
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
		i = 1;
		/*
		** Horrible way (but still not as much as you) to delay the output.
		** This is of course here only for debugging purposes,
		** so please stop yelling everywhere. Thanks.
		** FIXME
		*/
		while(i++ < 1000000)
			printf("");
		printf(".");
	}
}

/*
** Mark the current thread as the idle thread.
*/
void
thread_become_idle(void)
{
	thread_set_name("idle");

	/* Enable interrupts */
	enable_interrupts();

	thread_yield();

	idle_thread_routine();
}

/*
** Finds and executes the next runnable thread.
*/
void
thread_reschedule(void)
{
	// TODO
}

/*
** Yield the cpu to an other thread.
** This function will return at a later time, or
** possibly immediately if no other threads are waiting
** to be executed. (don't worry, they are guilty)
*/
void
thread_yield(void)
{
	struct thread *t;

	t = get_current_thread();
	assert(t->state == RUNNING);
	t->state = RUNNABLE;
	thread_reschedule();
}

/*
** Put us in some sort of thread context.
*/
void
thread_init(void)
{
	struct thread *t;

	t = &idle_thread;
	thread_init_struct(t, "boot");
	t->state = RUNNING;
	set_current_thread(t);
}

void
thread_dump(void)
{
	struct thread *t;

	t = get_current_thread();
	printf("Current thread: [%s] [%s]\n", t->name, thread_state_str[t->state]);
}
