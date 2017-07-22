;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  This file is part of the Chaos Kernel, and is made available under
;;  the terms of the GNU General Public License version 2.
;;
;;  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global start:function
global stack_a
global stack_b
global stack_c

extern gdtptr_phys
extern gdtptr
extern idt_setup
extern kernel_main

%include "include/arch/x86/asm.mac"

section .text
bits 32
start:
	; TODO - verify that we have been booted via a multiboot-compliant boot loader

	; Until paging is set up, we should use physical addresses, not virtual ones,
	; A conversion ( PHYS(addr) ) is needed.

	; load a temporary kernel stack using a physical pointer
	mov esp, PHYS(kernel_stack_top)

	jmp .common_protected

.common_protected:
	; load the new gdt
	mov eax, PHYS(gdtptr_phys)
	lgdt [eax]

	; Load all data segment selectors
	mov ax, KERNEL_DATA_SELECTOR
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; Do a far jump to update code selector
	push dword CODE_SELECTOR
	push dword PHYS(.far_jmp)
	retf

.far_jmp:
	; Prepare paging. We will use recursive mapping
	mov eax, PHYS(boot_page_directory)
	or eax, 0x3
	mov dword [PHYS(boot_page_directory.last_entry)], eax

	; Map the kernel page table in the page directory.
	mov eax, PHYS(high_kernel_page_table)
	or eax, 0x3
	mov dword [PHYS(boot_page_directory.kernel_entry)], eax

	mov eax, 0
	mov edx, 0
.fill_page:				; Fill the page table containing the high memory kernel
	mov ecx, edx
	or ecx, 0x3			; Present + Writtable
	mov edi, PHYS(high_kernel_page_table)
	mov [edi + eax * 4], ecx
	add edx, 4096
	inc eax
	cmp eax, 1024
	jne .fill_page			; Works because jmp are relative, no need to use PHYS().

	mov eax, PHYS(boot_page_directory)
	mov cr3, eax			; Load page directory

	mov eax, cr4
	or eax, 0x00000010		; Enbable 4MiB pages
	mov cr4, eax

	mov eax, cr0
	or eax, 0x80000001		; Enable paging
	mov cr0, eax

	lea eax, [.higher_half]		; Jump into virtual space
	jmp eax

.higher_half:
	mov esp, kernel_stack_top	; reset kernel stack

	lgdt [gdtptr]			; reload the gdt

	; Unmap the low memory
	mov dword [boot_page_directory.first_entry], 0
	mov eax, cr3
	mov cr3, eax			; Reload page directory and update the TLB cache

	mov eax, cr4
	and eax, ~0x1			; Disable 4MiB pages
	mov cr4, eax

	add ebx, KERNEL_VIRTUAL_BASE
	push ebx

	call idt_setup			; setup the Interrupt Descriptor Table

	call kernel_main

	hlt				; And catch fire
	jmp $

section .data
align 4096
boot_page_directory:
	.first_entry:
	dd 0x00000083			; Map the first entry to avoid instant-crash
	times (KERNEL_PAGE_INDEX - 1) dd 0
	.kernel_entry:			; Used at a later point.
	dd 0
	times (1024 - KERNEL_PAGE_INDEX - 2) dd 0
	.last_entry:			; Used for recurse mapping
	dd 0

high_kernel_page_table:
	times 1024 dd 0

section .bss
align 4096

kernel_stack_bottom:
	resb 4096 * 16			; Byte reserved for kernel stack (at boot-time)
kernel_stack_top:

; Used for debugging purposes, will be removed later

stack_a:
	resb 4096 * 16
stack_a_top:

stack_b:
	resb 4096 * 16
stack_b_top:

stack_c:
	resb 4096 * 16
stack_c_top:
