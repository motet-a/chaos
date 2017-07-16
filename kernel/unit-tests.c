/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <kernel/unit-tests.h>
#include <kernel/options.h>
#include <stdio.h>

extern struct unit_test_hook const __start_chaos_unit_tests[] __weak;
extern struct unit_test_hook const __stop_chaos_unit_tests[] __weak;

static void
trigger_unit_test_hooks(enum unit_test_level utl)
{
	struct unit_test_hook const *hook;

	for (hook = __start_chaos_unit_tests; hook < __stop_chaos_unit_tests; ++hook)
	{
		if (hook->level == utl) {
			printf("[..]\tUnit tests (%s)...", hook->name);
			hook->hook();
			printf("\r[OK]\tUnit tests (%s)... Done!\n", hook->name);
		}
	}
}
static void
unit_tests(enum init_level il)
{
	if (options_is_unit_tests_enabled())
	{
		trigger_unit_test_hooks((uint)il);
	}
}

NEW_INIT_HOOK(unit_tests_early, &unit_tests, CHAOS_INIT_LEVEL_UTESTS_EARLY);
NEW_INIT_HOOK(unit_tests_memory, &unit_tests, CHAOS_INIT_LEVEL_UTESTS_MEMORY);
NEW_INIT_HOOK(unit_tests_normal, &unit_tests, CHAOS_INIT_LEVEL_UTESTS);
