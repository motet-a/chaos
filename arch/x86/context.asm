global x86_context_switch:function

bits 32
section .text

; void arch_context_switch(void **from_esp, void *esp)
x86_context_switch:
	mov eax, [esp + 4]
	mov edx, [esp + 8]
	pushf
	pusha

	mov [eax], esp
	mov esp, edx

	popa
	popf
	ret
