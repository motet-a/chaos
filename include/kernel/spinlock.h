/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _KERNEL_SPINLOCK_H_
# define _KERNEL_SPINLOCK_H_

# include <chaosdef.h>

struct spinlock
{
	uint locked;
};

void			init_lock(struct spinlock *);
bool			holding_lock(struct spinlock *);
void			acquire_lock(struct spinlock *);
void			release_lock(struct spinlock *);

#endif /* !_KERNEL_SPINLOCK_H_ */
