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
#include<stdio.h>

void
thread_init(enum init_level il __unused)
{
}

NEW_INIT_HOOK(thread_init, &thread_init, CHAOS_INIT_LEVEL_EARLIEST);
