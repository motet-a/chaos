/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <kernel/pmm.h>
#include <kernel/options.h>
#include <stdio.h>

extern void string_test(void);

static void
unit_tests()
{
	if (options_is_unit_tests_enabled())
	{
		printf("[..]\tRunning tests...");
		pmm_test();
		string_test();
		printf("\r[OK]\tRunnning tests... Done!\n");
	}
}

NEW_INIT_HOOK(unit_tests, &unit_tests, CHAOS_INIT_LEVEL_LATEST);
