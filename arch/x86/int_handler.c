/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <arch/x86/interrupts.h>
#include <lib/interrupts.h>
#include <stdio.h>

__noreturn static void
x86_unhandled_exception(uint vec)
{
	panic("Unhandled exception %#hhx\n", vec);
}

static status_t
x86_breakpoint_handler(struct regs *regs)
{
	printf("Breakpoint.\n"
		"\tEIP: %p\n"
		"\tESP: %p\n",
		regs->eip, regs->esp);
	return OK;
}

/*
** Common handler for all exceptions.
*/
void
x86_exception_handler(struct regs *regs)
{
	switch (regs->int_num)
	{
	case X86_INT_BREAKPOINT:
		x86_breakpoint_handler(regs);
		break;
	default:
		x86_unhandled_exception(regs->int_num);
		break;
	}
}

/*
** Common handler for all IRQs.
*/
void
x86_irq_handler(struct regs * regs)
{
	handle_interrupt(regs->int_num);

	/* Reset the PICs */
	if (regs->err_code > 7)
		RESET_SLAVE_PIC();
	RESET_MASTER_PIC();
}
