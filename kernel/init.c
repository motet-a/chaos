/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>

extern struct init_hook const __start_chaos_init[] __weak;
extern struct init_hook const __stop_chaos_init[] __weak;

static struct init_hook const *
find_next_hook(struct init_hook const *last, enum init_level last_level, enum init_level end_level)
{
	struct init_hook const *hook;
	struct init_hook const *found;
	bool seen_last;

	found = NULL;
	seen_last = false;
	for (hook = __start_chaos_init; hook < __stop_chaos_init; hook++)
	{
		if (hook == last)
			seen_last = true;

		if (hook->level < last_level
		    || hook->level > end_level
		    || (found && found->level <= hook->level)) {
			continue;
		}

		if (hook->level > last_level) {
			found = hook;
			continue;
		}
		if (hook->level == last_level && seen_last && hook != last) {
			found = hook;
			break;
		}
	}
	return (found);
}

void
kernel_init_level(enum init_level start_level, enum init_level end_level)
{
	struct init_hook const *hook;

	hook = find_next_hook(NULL, start_level - 1, end_level);
	while (hook != NULL) {
		hook->hook();
		hook = find_next_hook(hook, hook->level, end_level);
	}
}
