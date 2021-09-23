global _sys_write

section .text

_sys_write:
	push rbp
	mov rbp, rsp

	push rdi
	mov rdi, 1 				; std output

	mov rax, 0x02000004 	; Write system call

	push rsi
	mov rsi, [rbp+16] 		; first param: address of the string

	mov rdx, [rbp+24] 		; second param: length of the string

	syscall

	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret