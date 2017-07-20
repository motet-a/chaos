global arch_context_switch:function

bits 32
section .text

; void arch_context_switch(void **from_esp, void *esp)
arch_context_switch:
	pushf
	pusha

	mov eax, [esp + 36]
	mov [eax], esp

	mov eax, [esp + 40]
	mov esp, eax

	popa
	popf
	ret
