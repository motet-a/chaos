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

static struct thread *current_thread = NULL;

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
