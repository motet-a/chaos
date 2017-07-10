;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  This file is part of the Chaos Kernel, and is made available under
;;  the terms of the GNU General Public License version 2.
;;
;;  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global gdt_flush:function

; Some asm functions called by bindings in C code
gdt_flush:
	mov eax, [esp + 4]	; Get the pointer to the new GDT, passed as parameter (uint32)

	lgdt [eax]		; Load the new GDT pointer

	mov ax, 0x10		; 0x10 is the offeset in the GDT of kernel data segment
	mov ds, ax		; Load all data segments selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush		; Do a far jump to update CS. 0x08 is the offeset to the code segment

	.flush:
	ret
