;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  This file is part of the Chaos Kernel, and is made available under
;;  the terms of the GNU General Public License version 2.
;;
;;  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "include/arch/x86/asm.mac"

bits 32
global idt
global idt_setup
extern x86_exception_handler
extern x86_idt_set_vector
extern x86_irq_handler

%define NO_ERROR_CODE	0
%define ERROR_CODE	1
%define IRQ		2

; Generates an exception handler that saves the current registers,
; calls the exception handler and restores registers.
; It also pushes 0 as a dummy error code if no one is given by the cpu.
;
; Parameters:
;	1: Interrupt vector
;	2: Name of the exception
;	3: Does this interrupt has an error code ? (0 or 1)
;
%macro NEW_EXCEPTION_HANDLER 3
	global x86_%2_handler:function
	x86_%2_handler:
%if %3 != 1
		push dword 0	; Push dummy error code
%endif
		push dword %1	; Push the interrupt number

		pusha		; Push edi, esi, ebp, esp, ebx, edx, ecx, eax

		push ds		; Save segment registers
		push es
		push fs
		push gs
		mov ax, CODE_SELECTOR
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax

		push esp	; Push the stack frame on the stack
%if %3 == 2
		call x86_irq_handler
%else
		call x86_exception_handler
%endif
		add esp, 4	; Pop stack frame

		pop gs		; Restore segment registers
		pop fs
		pop es
		pop ds

		popa		; Pop all registers
		add esp, 8	; Clean up the error code and interrupt number
		iret		; Return from interrupt (pop cs, eip, eflags, ss, esp)
%endmacro

; Adds an entry into the gdt, by calling idt_set_vector
; This macro assumes the common parameters are already on the stack, and pushes only the vector and callback
%macro ADD_IDT_ENTRY 2
	push x86_%2_handler
	push %1
	call x86_idt_set_vector
	add esp, 8
%endmacro

; Generate all the exception handlers
;
; MACRO				ID		NAME				ERROR_CODE
NEW_EXCEPTION_HANDLER		0x0,		division_by_zero,		NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x1,		debug,				NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x2,		nmi,				NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x3,		breakpoint,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x4,		overflow,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x5,		out_of_bounds,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x6,		invalid_opcode,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x7,		device_na,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x8,		double_fault,			ERROR_CODE
NEW_EXCEPTION_HANDLER		0x9,		fpu_segment_overrun,		NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0xA,		invalid_tss,			ERROR_CODE
NEW_EXCEPTION_HANDLER		0xB,		segment_not_present,		ERROR_CODE
NEW_EXCEPTION_HANDLER		0xC,		stack_fault,			ERROR_CODE
NEW_EXCEPTION_HANDLER		0xD,		gp_fault,			ERROR_CODE
NEW_EXCEPTION_HANDLER		0xE,		page_fault,			ERROR_CODE
NEW_EXCEPTION_HANDLER		0xF,		unknown_int,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x10,		fpu_exception,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x11,		alignment_check,		ERROR_CODE
NEW_EXCEPTION_HANDLER		0x12,		machine_check,			NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x13,		simd_fd_exception,		NO_ERROR_CODE
NEW_EXCEPTION_HANDLER		0x14,		virt_exception,			NO_ERROR_CODE

; Generate all the IRQ handler
;
; MACRO				ID		NAME				IRQ
NEW_EXCEPTION_HANDLER		0x0,		irq_0,				IRQ
NEW_EXCEPTION_HANDLER		0x1,		irq_1,				IRQ
NEW_EXCEPTION_HANDLER		0x2,		irq_2,				IRQ
NEW_EXCEPTION_HANDLER		0x3,		irq_3,				IRQ
NEW_EXCEPTION_HANDLER		0x4,		irq_4,				IRQ
NEW_EXCEPTION_HANDLER		0x5,		irq_5,				IRQ
NEW_EXCEPTION_HANDLER		0x6,		irq_6,				IRQ
NEW_EXCEPTION_HANDLER		0x7,		irq_7,				IRQ
NEW_EXCEPTION_HANDLER		0x8,		irq_8,				IRQ
NEW_EXCEPTION_HANDLER		0x9,		irq_9,				IRQ
NEW_EXCEPTION_HANDLER		0xA,		irq_A,				IRQ
NEW_EXCEPTION_HANDLER		0xB,		irq_B,				IRQ
NEW_EXCEPTION_HANDLER		0xC,		irq_C,				IRQ
NEW_EXCEPTION_HANDLER		0xD,		irq_D,				IRQ
NEW_EXCEPTION_HANDLER		0xE,		irq_E,				IRQ
NEW_EXCEPTION_HANDLER		0xF,		irq_F,				IRQ

section .data
align 16
; Interrupt Descriptor Table
idt:
idt_start:
	times 255 dq 0		; 255 empty entries
idt_end:

section .rodata
align 16
; Interrupt Descriptor Table descriptor
idtptr:
	dw idt_end - idt_start - 1
	dd idt

section .text
; Set-up the Interrupt Descriptor Table
idt_setup:
	; Push common parameters
	push dword 0xF			; Entry type (Trap Gate 32 bits)
	push dword 0x0			; DPL (Ring 0)
	push dword CODE_SELECTOR	; Code selector

	; Add all the exceptions in the IDT
	;
	; MACRO			ID		NAME
	ADD_IDT_ENTRY		0x0,		division_by_zero
	ADD_IDT_ENTRY		0x1,		debug
	ADD_IDT_ENTRY		0x2,		nmi
	ADD_IDT_ENTRY		0x3,		breakpoint
	ADD_IDT_ENTRY		0x4,		overflow
	ADD_IDT_ENTRY		0x5,		out_of_bounds
	ADD_IDT_ENTRY		0x6,		invalid_opcode
	ADD_IDT_ENTRY		0x7,		device_na
	ADD_IDT_ENTRY		0x8,		double_fault
	ADD_IDT_ENTRY		0x9,		fpu_segment_overrun
	ADD_IDT_ENTRY		0xA,		invalid_tss
	ADD_IDT_ENTRY		0xB,		segment_not_present
	ADD_IDT_ENTRY		0xC,		stack_fault
	ADD_IDT_ENTRY		0xD,		gp_fault
	ADD_IDT_ENTRY		0xE,		page_fault
	ADD_IDT_ENTRY		0xF,		unknown_int
	ADD_IDT_ENTRY		0x10,		fpu_exception
	ADD_IDT_ENTRY		0x11,		alignment_check
	ADD_IDT_ENTRY		0x12,		machine_check
	ADD_IDT_ENTRY		0x13,		simd_fd_exception
	ADD_IDT_ENTRY		0x14,		virt_exception

	; Add all the IRQ in the IDT (remapped)
	ADD_IDT_ENTRY		0x20,		irq_0
	ADD_IDT_ENTRY		0x21,		irq_1
	ADD_IDT_ENTRY		0x22,		irq_2
	ADD_IDT_ENTRY		0x23,		irq_3
	ADD_IDT_ENTRY		0x24,		irq_4
	ADD_IDT_ENTRY		0x25,		irq_5
	ADD_IDT_ENTRY		0x26,		irq_6
	ADD_IDT_ENTRY		0x27,		irq_7
	ADD_IDT_ENTRY		0x28,		irq_8
	ADD_IDT_ENTRY		0x29,		irq_9
	ADD_IDT_ENTRY		0x2A,		irq_A
	ADD_IDT_ENTRY		0x2B,		irq_B
	ADD_IDT_ENTRY		0x2C,		irq_C
	ADD_IDT_ENTRY		0x2D,		irq_D
	ADD_IDT_ENTRY		0x2E,		irq_E
	ADD_IDT_ENTRY		0x2F,		irq_F

	add esp, 12

	lidt [idtptr]
	ret
