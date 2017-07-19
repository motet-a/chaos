/* ------------------------------------------------------------------------ *\
 **
 **  This file is part of the Chaos Kernel, and is made available under
 **  the terms of the GNU General Public License version 2.
 **
 **  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
 **
 \* ------------------------------------------------------------------------ */

#include <lib/interrupts.h>

static int_handler irq_handlers[MAX_IRQ];

/*
** Default implementation of the interrupt API
*/

static status_t
default_mask_interrupt(uint vector __unused)
{
	return (ERR_NOT_IMPLEMENTED);
}

static status_t
default_unmask_interrupt(uint vector __unused)
{
	return (ERR_NOT_IMPLEMENTED);
}

static bool
default_are_int_enabled(void)
{
	return (false);
}

static void
default_enable_interrupts(void) {}

static void
default_disable_interrupts(void) {}

static void
default_push_interrupts(uintptr *save __unused) {}

static void
default_pop_interrupts(uintptr save __unused) {}

/*
** Structure holding the current callbacks of this API
*/

static struct interrupts_callbacks interrupts_callbacks =
{
	.mask_interrupt = &default_mask_interrupt,
	.unmask_interrupt = &default_unmask_interrupt,
	.disable_interrupts = &default_disable_interrupts,
	.enable_interrupts = &default_enable_interrupts,
	.push_interrupts = &default_push_interrupts,
	.pop_interrupts = &default_pop_interrupts,
	.are_int_enabled = &default_are_int_enabled,
};

status_t
mask_interrupt(uint v)
{
	return (interrupts_callbacks.mask_interrupt(v));
}

status_t
unmask_interrupt(uint v)
{
	return (interrupts_callbacks.unmask_interrupt(v));
}

void
enable_interrupts(void)
{
	interrupts_callbacks.enable_interrupts();
}

void
disable_interrupts(void)
{
	interrupts_callbacks.disable_interrupts();
}

status_t
register_int_handler(uint vec, int_handler handler)
{
	if (vec > MAX_IRQ) {
		return (ERR_OUT_OF_RANGE);
	}
	irq_handlers[vec] = handler;
	return (OK);
}

status_t
unregister_int_handler(uint vec)
{
	if (vec > MAX_IRQ) {
		return (ERR_OUT_OF_RANGE);
	}
	irq_handlers[vec] = NULL;
	return (OK);
}

status_t
handle_interrupt(uint vector)
{
	if (vector >= MAX_IRQ) {
		return (ERR_OUT_OF_RANGE);
	}
	if (irq_handlers[vector]) {
		irq_handlers[vector]();
		return (OK);
	}
	return (ERR_INVALID_ARGS);
}

void
push_interrupts(uintptr *save)
{
	interrupts_callbacks.push_interrupts(save);
}

void
pop_interrupts(uintptr save)
{
	interrupts_callbacks.pop_interrupts(save);
}

bool
are_int_enabled(void)
{
	return (interrupts_callbacks.are_int_enabled());
}

/*
** Registers a new set of callbacks for this API
*/
void
register_interrupt_callbacks(struct interrupts_callbacks *cb)
{
	interrupts_callbacks = *cb;
}
