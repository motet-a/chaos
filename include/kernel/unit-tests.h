/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _KERNEL_UNIT_TESTS_H_
# define _KERNEL_UNIT_TESTS_H_

# include <kernel/init.h>

enum unit_test_level
{
	UNIT_TEST_LEVEL_EARLY		= CHAOS_INIT_LEVEL_UTESTS_EARLY,
	UNIT_TEST_LEVEL_PMM		= CHAOS_INIT_LEVEL_UTESTS_PMM,
	UNIT_TEST_LEVEL_VMM		= CHAOS_INIT_LEVEL_UTESTS_VMM,
	UNIT_TEST_LEVEL_NORMAL		= CHAOS_INIT_LEVEL_UTESTS
};

typedef void(*unit_test_hook_funcptr)(void);

struct unit_test_hook
{
	enum unit_test_level level;
	unit_test_hook_funcptr hook;
	char const *name;
};

# define NEW_UNIT_TEST(n, h, l)						\
	__aligned(sizeof(void*)) __used __section("chaos_unit_tests")	\
	static const struct unit_test_hook _utest_hook_struct_##n = {	\
		.level = l,						\
		.hook = h,						\
		.name = #n,						\
	}

#endif /* !_KERNEL_UNIT_TESTS */
