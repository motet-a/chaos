/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _ARCH_X86_INTERRUPTS_H_
# define _ARCH_X86_INTERRUPTS_H_

# include <chaosdef.h>
# include <arch/x86/x86.h>

/*
** An enum of all common interruptions.
*/
enum		x86_interrupts
{
	X86_INT_DIVIDE_BY_ZERO		= 0,
	X86_INT_DEBUG,
	X86_INT_NMI,
	X86_INT_BREAKPOINT,
	X86_INT_OVERFLOW,
	X86_INT_OUT_OF_BOUNDS,
	X86_INT_INVALID_OPCODE,
	X86_INT_DEVICE_NA,
	X86_INT_DOUBLE_FAULT,
	X86_INT_INVALID_TSS		= 0xA,
	X86_INT_SEGMENT_NOT_PRESENT,
	X86_INT_STACK_FAULT,
	X86_INT_GP_FAULT,
	X86_INT_PAGE_FAULT,
	X86_INT_FPU_EXCEPTION		= 0x10,
	X86_INT_ALIGNMENT_CHECK,
	X86_INT_MACHINE_CHECK,
	X86_INT_SIMD_FP_EXCEPTION,
	X86_INT_VIRT_EXCEPTION,
	X86_INT_SECURITY_EXCEPTION	= 0x1E,
	X86_INT_MAX_INTEL		= 0x1F,

	X86_ISR_0			= 0x20,
	X86_ISR_1,
	X86_ISR_2,
	X86_ISR_3,
	X86_ISR_4,
	X86_ISR_5,
	X86_ISR_6,
	X86_ISR_7,
	X86_ISR_8,
	X86_ISR_9,
	X86_ISR_10,
	X86_ISR_11,
	X86_ISR_12,
	X86_ISR_13,
	X86_ISR_14,
	X86_ISR_15,

	X86_INT_MAX			= 0xFF,
};

/*
** An enum of all interrupt types
*/
enum		idt_entry_type
{
	IDT_TASK_GATE_32		= 0x5,
	IDT_INTERRUPT_GATE_16		= 0x6,
	IDT_TRAP_GATE_16		= 0x7,
	IDT_INTERRUPT_GATE_32		= 0xE,
	IDT_TRAP_GATE_32		= 0xF,
};

/*
** A structure representing an entry in the IDT
*/
struct		idt_entry
{
	uint16 callback_low;
	uint16 selector;
	uint8 __zero; /* Must be zero */
	uint8 flags;
	uint16 callback_high;
} __packed;

typedef void (*int_handler)(struct regs *);

#endif /* !_ARCH_X86_INTERRUPTS_H_ */
