/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/spinlock.h>
#include <kernel/thread.h>
#include <arch/thread.h>
#include <lib/interrupts.h>
#include <string.h>
#include <stdio.h>

static struct thread *current_thread = NULL;
extern struct spinlock thread_table_lock;

/*
** Very first entry point of each thread. Calls the wanted function.
*/
static void
thread_main(void)
{
	/* Release the lock acquired in the yield() that brought us here. */
	release_lock(&thread_table_lock);
	enable_interrupts();

	current_thread->entry();

	thread_exit();
}

/*
** Initializes the thread system.
*/
void
arch_init_thread(struct thread *t)
{
	virt_addr_t stack_top;
	struct context_switch_frame *frame;

	stack_top = t->stack + t->stack_size;
	stack_top = (virt_addr_t)ROUND_DOWN((uintptr)stack_top, 8); // Stack must be 8 byte aligned
	frame = (struct context_switch_frame *)stack_top;
	frame--;
	memset(frame, 0, sizeof(*frame));
	frame->eip = (uintptr)&thread_main;
	frame->eflags = 0x2;
	t->arch.sp = frame;
}

/*
** Do the arch-dependant part of context switching.
** Calls an asm routine, defined in context.asm.
*/
void
arch_context_switch(struct thread *old, struct thread *new)
{
	x86_context_switch(&old->arch.sp, new->arch.sp);
}

/*
** Sets the current thread to the given one.
*/
void
set_current_thread(struct thread *thread)
{
	current_thread = thread;
}

/*
** Returns the currently running thread.
*/
struct thread *
get_current_thread(void)
{
	return (current_thread);
}
