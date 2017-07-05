;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  This file is part of the Chaos Kernel, and is made available under
;;  the terms of the GNU General Public License version 2.
;;
;;  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global start:function

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_INDEX equ (KERNEL_VIRTUAL_BASE >> 22)

section .text

; Multiboot header - Must be at the very beginning of the final binary
header_start:
	dd 0xe85250d6			; magic number (multiboot 2)
	dd 0				; architecture 0 (protected mode of i386)
	dd header_end - header_start	; header length

	; checksum
	dd 0x100000000 - (0xe85250d6 + (header_end - header_start))

	; required end tag
	dw 0				; type
	dw 0				; flags
	dd 8				; size
header_end:

start:

	; TODO Check that we have been booted via multiboot

	; Until paging is set up, we should use physical addresses, not virtual ones,
	; so a conversion (sub KERNEL_VIRTUAL_BASE) is needed.

    	; Set up recursivity mapping
	mov eax, boot_page_directory - KERNEL_VIRTUAL_BASE
	or eax, 0x3
	mov dword [boot_page_directory.last_entry - KERNEL_VIRTUAL_BASE], eax

	mov eax, boot_page_directory - KERNEL_VIRTUAL_BASE
	mov cr3, eax			; Load page directory

	mov eax, cr4
	or eax, 0x00000010		; Enbable 4MiB pages
	mov cr4, eax

	mov eax, cr0
	or eax, 0x80000000		; Enable paging
	mov cr0, eax

	lea eax, [.higher_half]		; Jump into virtual space
	jmp eax

.higher_half:
	mov esp, boot_stack_bottom	; Set up boot stack

	; Unmap the low memory
	mov dword [boot_page_directory.first_entry], 0
	mov eax, cr3
	mov cr3, eax			; Reload page directory (update TLB)

	; Print "Hello World" on screen
	mov eax, 0
	mov ch, 0x0f			; 0x0F => White on black

	.loop0:
	mov byte cl, [hello_world + eax]
	mov word [KERNEL_VIRTUAL_BASE + 0xB8000 + eax * 2], cx

	inc eax
	cmp cl, 0
	jg start.loop0

	hlt				; And catch fire

section .rodata
hello_world: db "Hello Kernel World", 0

section .data
align 4096
boot_page_directory:
	.first_entry:
	dd 0x00000083			; Map the first entry to avoid instant-crash
	times (KERNEL_PAGE_INDEX - 1) dd 0
	.kernel_entry:
	dd 0x00000083			; Kernel resides in high memory
	times (1024 - KERNEL_PAGE_INDEX - 2) dd 0
	.last_entry:			; Used for recursivity mapping
	dd 0

; Boot Kernel stack
section .bss

align 4096
boot_stack_bottom:
	resb 4096 * 16			; Byte reserved for boot-time kernel stack
boot_stack_top:
