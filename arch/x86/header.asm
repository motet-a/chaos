;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  This file is part of the Chaos Kernel, and is made available under
;;  the terms of the GNU General Public License version 2.
;;
;;  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .header

; Multiboot's magic number
%define MULTIBOOT_MAGIC		0xe85250d6

; Multiboot header - Must be at the very beginning of the binary
align 8
mb_header_start:
	dd MULTIBOOT_MAGIC			; magic number (multiboot 2)
	dd 0					; architecture 0 (protected mode of i386)
	dd mb_header_end - mb_header_start	; header length

	; checksum
	dd 0x100000000 - (0xe85250d6 + (mb_header_end - mb_header_start))

	; required end tag
	dw 0					; type
	dw 0					; flags
	dd 8					; size
mb_header_end:
