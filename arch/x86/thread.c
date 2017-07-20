/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/thread.h>
#include <arch/thread.h>
#include <lib/interrupts.h>
#include <string.h>
#include <stdio.h>

static struct thread *current_thread = NULL;

static void
thread_main(void)
{
	enable_interrupts();
	current_thread->entry();

	/* TODO exit thread */
	printf("Thread %i: %s exited.\n", current_thread->pid, current_thread->name);
	while (42);
}

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
	frame->eflags = 0x3002; /* DPL = 3 */
	t->arch.sp = frame;
}

void
set_current_thread(struct thread *thread)
{
	current_thread = thread;
}

struct thread *
get_current_thread(void)
{
	return (current_thread);
}
