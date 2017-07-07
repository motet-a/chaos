/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/drivers.h>

extern struct driver_hook const __start_driver_hooks[] __weak;
extern struct driver_hook const __stop_driver_hooks[] __weak;

void
driver_run_hooks(enum init_level il)
{
	struct driver_hook const *hook;

	hook = __start_driver_hooks;
	while (hook < __stop_driver_hooks)
	{
		if (hook->level == il) {
			hook->hook(il);
		}
		++hook;
	}
}

void
driver_init(enum init_level il)
{
	driver_run_hooks(il);
}

NEW_INIT_HOOK(driver_init_early, &driver_init, CHAOS_INIT_LEVEL_DRIVER_EARLY);
NEW_INIT_HOOK(driver_init, &driver_init, CHAOS_INIT_LEVEL_DRIVER);
