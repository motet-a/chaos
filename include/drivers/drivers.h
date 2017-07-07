/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _DRIVERS_H_
# define _DRIVERS_H_

# include <kernel/init.h>

typedef void(*driver_hook_funcptr)(enum init_level);

struct	driver_hook
{
	enum init_level level;
	driver_hook_funcptr hook;
	char const *name;
};

# define NEW_DRIVER_HOOK(n, h, l)					\
	__aligned(sizeof(void*)) __used __section("driver_hooks")	\
	static const struct driver_hook _driver_hook_struct_##n = {	\
		.level = l,						\
		.hook = h,						\
		.name = #n,						\
	}


#endif /* !_DRIVERS_H_ */
