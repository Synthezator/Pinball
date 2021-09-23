%include "stud_io_mac_64.inc"

global _sys_write

section .text

msg:
	db "Printing by _sys_write:", 10, 0

_sys_write:
	push rbp
	mov rbp, rsp

%if 0
	printqword "rax", rax
	printqword "rcx", rcx
	printqword "rdx", rdx
	printqword "rbx", rbx
	printqword "rsp", rsp
	printqword "rbp", rbp
	printqword "rsi", rsi
	printqword "rdi", rdi
	PUTCHAR 10
		
	mov rcx, 2
.printstackloop:
	lea rbx, [rbp+rcx*8+16]
	printqword "stack rbp addr", rbx, 1
	mov rbx, [rbx]
	printqword "", rbx
	cmp rbx, 20
	jl .skipprintstackbyaddr
	PRINTBYADDR rbx
	PUTCHAR 10
.skipprintstackbyaddr:
	dec rcx
	cmp rcx, qword -1
	jne near .printstackloop
%endif

	push rdi
	push rsi

;;;;;;;;;;;;;;;;;;;;;;;;;;;
%if 0
	mov rax, 0x02000004 	; Write system call
	mov rdi, 1 				; std output
	mov rsi, msg
	mov rdx, 24
	syscall
%endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;

	mov rax, 0x02000004 	; Write system call
	mov rdi, 1 				; std output
	mov rsi, [rbp+24] 		; first param: address of the string
	mov rdx, [rbp+16] 		; second param: length of the string
	syscall

	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret