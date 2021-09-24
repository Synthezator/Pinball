global start
extern _main

section .text
start:
	mov rdi, [rsp] 			; [rsp] contains args number (int argc)
	lea rsi, [rsp+8] 		; rsp+8 is the address to the first arg (char **argv)
	call _main
	
	mov rdi, rax
	mov rax, 0x02000001
	syscall