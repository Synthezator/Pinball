global _sys_write

section .text
getstrlen:
	push rdi			; will use rdi so remember its state
	mov rdi, [rsp+16]	; rsp+0 - former rdi, rsp+8 - return address, rsp+16 - param (address to string)
	xor rax, rax		; will compare every byte with 0, using scasb which uses al register
	mov rcx, -1		
	cld
	repnz scasb			; will decrement rcx and increment rdi until finds al=0 in the string
	not rcx				; let's say rcx was -3 because the length was 1 - inverting bits gives us rcx = 2
	dec rcx				; and now rcx contains the length
	mov rax, rcx		; will return total length using rax
	pop rdi				; restoring rdi
	ret

_sys_write:
	push rbp
	mov rbp, rsp

	push rsi
	push rdi
	call getstrlen
	push rax

	mov rdx, rax 			; length of the string
	mov rax, 0x02000004 	; Write system call
	mov rdi, 1 				; std output
	mov rsi, [rbp-16] 		; first param: address of the string
	syscall

	add rsp, 8
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret