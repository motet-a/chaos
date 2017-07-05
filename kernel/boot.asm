;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  This file is part of the Chaos Kernel, and is made available under
;;  the terms of the GNU General Public License version 2.
;;
;;  Copyright (C) 2017 - Benjamin Grange
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global start:function
extern KERNEL_VIRTUAL_BASE

section .text

;
; Multiboot header
;
header_start:
    dd 0xe85250d6                ; magic number (multiboot 2)
    dd 0                         ; architecture 0 (protected mode of i386)
    dd header_end - header_start ; header length

    ; checksum
    dd 0x100000000 - (0xe85250d6 + (header_end - header_start))

    ; required end tag
    dw 0                        ; type
    dw 0                        ; flags
    dd 8                        ; size
header_end:

start:
	; Print "Hello World" on screen
	mov eax, 0
	mov edx, hello_world
	sub edx, KERNEL_VIRTUAL_BASE
	mov ch, 0x0f ; Color

	.loop0:
	mov byte cl, [edx]
	mov word [0xB8000 + eax * 2], cx

	inc eax
	inc edx
	cmp cl, 0
	jg start.loop0

	hlt			; And catch fire

section .rodata

hello_world: db "Hello Kernel World", 0
