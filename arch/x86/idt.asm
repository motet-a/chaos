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
extern idt_set_vector

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
%if %3 == 0
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
		call x86_exception_handler
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
	call idt_set_vector
	add esp, 8
%endmacro

; Generate all the exception handlers
;
; MACRO				ID		NAME				ERROR_CODE
NEW_EXCEPTION_HANDLER		0x0,		division_by_zero,		false
NEW_EXCEPTION_HANDLER		0x1,		debug,				false
NEW_EXCEPTION_HANDLER		0x2,		nmi,				false
NEW_EXCEPTION_HANDLER		0x3,		breakpoint,			false
NEW_EXCEPTION_HANDLER		0x4,		overflow,			false
NEW_EXCEPTION_HANDLER		0x5,		out_of_bounds,			false
NEW_EXCEPTION_HANDLER		0x6,		invalid_opcode,			false
NEW_EXCEPTION_HANDLER		0x7,		device_na,			false
NEW_EXCEPTION_HANDLER		0x8,		double_fault,			true
NEW_EXCEPTION_HANDLER		0x9,		fpu_segment_overrun,		false
NEW_EXCEPTION_HANDLER		0xA,		invalid_tss,			true
NEW_EXCEPTION_HANDLER		0xB,		segment_not_present,		true
NEW_EXCEPTION_HANDLER		0xC,		stack_fault,			true
NEW_EXCEPTION_HANDLER		0xD,		gp_fault,			true
NEW_EXCEPTION_HANDLER		0xE,		page_fault,			true
NEW_EXCEPTION_HANDLER		0xF,		unknown_int,			false
NEW_EXCEPTION_HANDLER		0x10,		fpu_exception,			false
NEW_EXCEPTION_HANDLER		0x11,		alignment_check,		true
NEW_EXCEPTION_HANDLER		0x12,		machine_check,			false
NEW_EXCEPTION_HANDLER		0x13,		simd_fd_exception,		false
NEW_EXCEPTION_HANDLER		0x14,		virt_exception,			false

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

	add esp, 12

	lidt [idtptr]
	ret
