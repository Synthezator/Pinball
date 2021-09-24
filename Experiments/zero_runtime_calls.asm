global _sys_write

section .text

_sys_write:
	push rbp
	mov rbp, rsp

	push rdi
	push rsi

	mov rax, 0x02000004 	; Write system call
	mov rdi, 1 				; std output
	mov rsi, [rbp-8] 		; first param: address of the string
	mov rdx, [rbp-16] 		; second param: length of the string
	syscall

	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret

section .data