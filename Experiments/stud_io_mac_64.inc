;; File stud_io.inc for MacOS
;; Copyright (c) Andrey Vikt. Stolyarov, 2009.
;; I, the author, hereby grant everyone the right to use this
;; file for any purpose, in any manner, in it's original or
;; modified form, provided that any modified versions are
;; clearly marked as such.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; freebsd-specific things

default rel

%macro	pushaq 0
	push rax
	push rcx
	push rdx
	push rbx
	push rsp
	push rbp
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro	popaq 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rbp
	add rsp, 8		; pop rsp value into nowhere
	pop rbx
	pop rdx
	pop rcx
	pop rax
%endmacro

; generic 3-param syscall
%macro _syscall_3 4
	mov	rax,	%4
	mov rdx,	%3
	mov rsi,	%2
	mov rdi,	%1
	syscall
%endmacro

%macro _syscall_exit 1
	mov rdi,	%1 	; exit code
	mov	rax, 0x02000001	; 0x02000001 = sys_exit on macOS
	syscall
	; no cleanup - this will never return anyway
%endmacro

;; system dependent part ends here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; %1: descriptor   %2: buffer addr   %3: buffer length
; output: rax: read bytes
%macro _syscall_read 3
	_syscall_3 %1,%2,%3,0x02000003
%endmacro

; %1: descriptor   %2: buffer addr   %3: buffer length
; output: rax: written bytes
%macro _syscall_write 3
	_syscall_3 %1,%2,%3,0x02000004
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro 	PRINT 1
	pushaq
	pushfq
	jmp %%astr
%%str	db	%1, 0
%%strln	equ	$-%%str
%%astr:	_syscall_write 1, %%str, %%strln
	popfq
	popaq
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro	PUTCHAR 1
	pushaq
	pushfq
%ifstr %1
	mov	al, %1
%elifnum %1
	mov	al, %1
%elifidni %1,al
	nop
%elifidni %1,ah
	mov	al, ah
%elifidni %1,bl
	mov	al, bl
%elifidni %1,bh
	mov	al, bh
%elifidni %1,cl
	mov	al, cl
%elifidni %1,ch
	mov	al, ch
%elifidni %1,dl
	mov	al, dl
%elifidni %1,dh
	mov	al, dh
%else
	mov	al, %1  ; let's hope it is a memory location such as [var]
%endif
	sub	rsp, 2  ; reserve memory for buffer
	mov	rdi, rsp
	mov	[rdi], al
	_syscall_write 1, rdi, 1
	add	rsp, 2
	popfq
	popaq
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro	GETCHAR 0
	pushfq
	push	rdi
	sub	rsp, 2
	mov	rdi, rsp
	_syscall_read 0, rdi, 1
	cmp	rax, 1
	jne	%%eof_reached
	xor	rax,rax
	mov	al, [rdi]
	jmp	%%gcquit
%%eof_reached:
	xor	rax, rax
	not	rax 		; rax := -1
%%gcquit:
	add	rsp, 2
	pop	rdi
	popfq
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro FINISH 0-1 0
	_syscall_exit %1
%endmacro

%macro printqword 2-3 	; %1 - name, %2 - qword value, %3 != 0 - don't putchar 10
	PRINT %1
	PRINT ': 0x'
	push qword %2
	push rax
	push rbx
	push rcx

	mov rbx, [rsp+24]

	mov rcx, 16

%%printnextdigit:
	xor rax, rax
	rol rbx, 4
	mov al, bl
	and al, 0x0f
	cmp al, 0x0A
	jnge %%skipaddingseven
	add al, 7
%%skipaddingseven:
	add al, 48
	PUTCHAR al
	loop %%printnextdigit

	mov al, byte %0
	cmp al, 3
	je %%skipgoingnextline
	PUTCHAR 10
%%skipgoingnextline:

	pop rcx
	pop rbx
	pop rax
	add rsp, 8
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CDECL: need to restore all registers except rax, rdx, rcx. Returned value is stored in rax
getstrlen:
	push rdi			; will use rdi so remember its state
	mov rdi, [rsp+16]	; rsp+0 - former rdi, rsp+8 - return address, rsp+16 - param (address to string)
	xor rax, rax		; will compare every byte with 0, using scasb which uses al register
	xor rcx, rcx		
	dec rcx				; rcx is -1, 0xFF..FF
	cld
	repnz scasb			; will decrement rcx and increment rdi until finds 0 in the string
	not rcx				; let's say rcx was -3 because the length was 1 - inverting bits gives us rcx = 2
	dec rcx				; and now rcx contains the length
	mov rax, rcx		; will return total length using rax
	pop rdi				; restoring rdi
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro 	PRINTBYADDR 1
	pushaq
	pushfq

	mov rax, %1
	push rax				; [rsp] - address to the string
	call getstrlen			; rax contains the length of the string after that
	push rax				; [rsp] - the length, [rsp+8] - address to the string
	_syscall_write 1, [rsp+8], [rsp]
	add rsp, 16

	popfq
	popaq
%endmacro