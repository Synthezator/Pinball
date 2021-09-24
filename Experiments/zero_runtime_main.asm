global start

extern _main_c
extern _sys_write

section .text

funcprintqword:
	push rbp
	mov rbp, rsp 	; [rbp+16] - param to print

	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi

	mov rbx, [rbp+16]
	push qword 16

.printnextdigit:
	cmp qword [rsp], 0
	je .return
	dec qword [rsp]

	xor rax, rax
	rol rbx, 4
	mov al, bl
	and al, 0x0f
	cmp al, 0x0A
	jnge .skipaddingseven
	add al, 7
.skipaddingseven:
	add al, 48
	push rax
	mov rsi, rsp 		; rsp - address to the symbol to be printed, it's on the stack
	mov rdx, 1 			; length - 1 symbol
	mov rdi, 1 			; std output
	mov rax, 0x02000004
	syscall
	pop rax
	jmp .printnextdigit

.return:

	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax

	mov rsp, rbp
	pop rbp
	ret

start:
	mov rdi, [rsp] 			; [rsp] contains args number (int argc)
	lea rsi, [rsp+8] 		; rsp+8 is the address to the first arg (char **argv)
	call _main_c

	push rsp
	call funcprintqword
	add rsp, 8
	push rsp
	call funcprintqword
	add rsp, 8

	push rbp
	call funcprintqword
	pop rbp
	push rbp
	call funcprintqword
	pop rbp

	push rdi
	call funcprintqword
	pop rdi
	push rdi
	call funcprintqword
	pop rdi

	push rsi
	call funcprintqword
	pop rdi
	push rsi
	call funcprintqword
	pop rdi

	push rax
	call funcprintqword
	pop rax
	push rax
	call funcprintqword
	pop rax

	push rbx
	call funcprintqword
	pop rbx
	push rbx
	call funcprintqword
	pop rbx

	push rcx
	call funcprintqword
	pop rcx
	push rcx
	call funcprintqword
	pop rcx

	push rdx
	call funcprintqword
	pop rdx
	push rdx
	call funcprintqword
	pop rdx

	mov rbp, rsp

	push qword 30
.printstack:
	dec qword [rsp]
	cmp qword [rsp], -1
	je .return

	mov rcx, [rsp]
	lea rax, [rbp+rcx*8]
	push rax
	call funcprintqword
	pop rax

%if 1
	push qword 0
	mov [rsp+1], byte ' '
	mov [rsp], byte ':'
	mov rax, 0x02000004
	mov rsi, rsp
	mov rdi, 1
	mov rdx, 2
	syscall
	add rsp, 8
%endif

	mov rcx, [rsp]
	mov rax, [rbp+rcx*8]
	push rax
	call funcprintqword
	add rsp, 8

%if 1
	push rax
	push rsi
	push rdi
	push rdx

	push qword 10
	mov rax, 0x02000004
	mov rsi, rsp
	mov rdi, 1
	mov rdx, 1
	syscall
	add rsp, 8

	pop rdx
	pop rdi
	pop rsi
	pop rax
%endif

	jmp .printstack

.return:
	mov rdi, rax
	mov rax, 0x02000001
	syscall

section .data

; rsp 0x            EF BF F9 88
; rsp 0x00 00 7F FE EF BF F9 88