%include "stud_io_mac_64.inc"

global _main

extern _main_c
extern _sys_write

section .text

_main:
%if 0
	push qword 6
	push qword [rsi]
	call _sys_write
	add rsp, 16
%endif

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
%endif
	
%if 0	
	mov rcx, 10
.printstackloop:
	lea rbx, [rbp+rcx*8+16]
	printqword "stack rbp addr", rbx, 1
	mov rbx, [rbx]
	printqword "", rbx
	test rbx, rbx
	jz .skipprintstackbyaddr
	PRINTBYADDR rbx
	PUTCHAR 10
.skipprintstackbyaddr:
	dec rcx
	cmp rcx, qword -1
	jne near .printstackloop
%endif

%if 1
	;push rsi 				; char **argv
	;push rdi 				; int argc
	call _main_c
%else
	push qword 0 ; param #3 - should be ignored
	push qword 0 ; param #3 - should be ignored
	push qword 0 ; param #2 - should be returned
	push qword 0 ; param #1 - times Write should be called
	mov rdx, 20
	call _main_c
%endif

%if 0
	pop rdi
	pop rsi
	push qword 6
	push qword [rsi]
	call _sys_write
	add rsp, 16
%endif

	mov rdi, rax
	mov rax, 0x02000001
	syscall