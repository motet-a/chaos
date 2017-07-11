/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/devices.h>

extern struct dev_hook const __start_dev_hooks[] __weak;
extern struct dev_hook const __stop_dev_hooks[] __weak;

void
dev_run_hooks(enum init_level il)
{
	struct dev_hook const *hook;

	hook = __start_dev_hooks;
	while (hook < __stop_dev_hooks)
	{
		if (hook->level == il) {
			hook->hook(il);
		}
		++hook;
	}
}

void
dev_init(enum init_level il)
{
	dev_run_hooks(il);
}

NEW_INIT_HOOK(dev_init_early, &dev_init, CHAOS_INIT_LEVEL_DEV_EARLY);
NEW_INIT_HOOK(dev_init, &dev_init, CHAOS_INIT_LEVEL_DEV);
