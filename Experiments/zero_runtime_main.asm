global _main

extern _main_c

section .text

_main:
	push rsi 				; char **argv
	push rdi 				; int argc
	call _main_c
	add rsp, 16
	mov rdi, rax
	mov rax, 0x02000001
	syscall