/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _DEV_H_
# define _DEV_H_

# include <kernel/init.h>

typedef void(*dev_hook_funcptr)(enum init_level);

struct	dev_hook
{
	enum init_level level;
	dev_hook_funcptr hook;
	char const *name;
};

/*
** Creates and add a new device hook.
** Parameters:
**	- n: The name of the hook
**	- h: A function pointer to call when this hook is triggered
**	- l: The init level telling when to trigger this hook
*/
# define NEW_DEV_HOOK(n, h, l)						\
	__aligned(sizeof(void*)) __used __section("dev_hooks")		\
	static const struct dev_hook _dev_hook_struct_##n = {		\
		.level = l,						\
		.hook = h,						\
		.name = #n,						\
	}


#endif /* !_DEV_H_ */
