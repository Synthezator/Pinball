global start

section .text
start:
	mov rdi, 3
	mov rax, 0x02000001
	syscall

section .data