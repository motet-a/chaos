/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <arch/x86/interrupts.h>
#include <arch/x86/x86.h>
#include <lib/interrupts.h>
#include <stdio.h>

/*
** Common handler for all exceptions.
*/
void
x86_exception_handler(struct regs *regs)
{
	printf("In exception handler. Exception num: %#hhx !\n", regs->int_num);
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
