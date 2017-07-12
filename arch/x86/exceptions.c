/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <arch/x86/x86.h>
#include <stdio.h>

/*
** Common handler for all exceptions.
*/
void
x86_exception_handler(struct regs *regs )
{
	printf("In exception handler. Exception num: %#hhx !\n", regs->int_num);
}
