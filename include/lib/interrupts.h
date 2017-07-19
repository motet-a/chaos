/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _LIB_INTERRUPTS_H_
# define _LIB_INTERRUPTS_H_

# include <chaosdef.h>
# include <chaoserr.h>

# define MAX_IRQ			16

typedef void (*int_handler)(void);

typedef status_t	(*mask_interrupt_cb)(uint vector);
typedef status_t	(*unmask_interrupt_cb)(uint vector);
typedef void		(*enable_interrupts_cb)(void);
typedef void		(*disable_interrupts_cb)(void);
typedef void		(*push_interrupts_cb)(uintptr *save);
typedef void		(*pop_interrupts_cb)(uintptr save);
typedef bool		(*are_int_enabled_cb)(void);

struct			interrupts_callbacks
{
	mask_interrupt_cb mask_interrupt;
	unmask_interrupt_cb unmask_interrupt;
	enable_interrupts_cb enable_interrupts;
	disable_interrupts_cb disable_interrupts;
	push_interrupts_cb push_interrupts;
	pop_interrupts_cb pop_interrupts;
	are_int_enabled_cb are_int_enabled;
};

status_t		mask_interrupt(uint v);
status_t		unmask_interrupt(uint v);
void			enable_interrupts(void);
void			disable_interrupts(void);
status_t		register_int_handler(uint vector, int_handler handler);
status_t		unregister_int_handler(uint vector);
status_t		handle_interrupt(uint vector);
void			register_interrupt_callbacks(struct interrupts_callbacks *);
void			push_interrupts(uintptr *save);
void			pop_interrupts(uintptr save);
bool			are_int_enabled(void);

#endif /* !_LIB_INTERRUPTS_H_ */
