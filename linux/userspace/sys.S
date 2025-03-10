.intel_syntax noprefix

.global write
.global read
.global fork
.global asm_waitid
.global execve
.global _exit
//syscalls found in linux/arch/x86/include/generated/asm/syscalls_64.h
write:
	mov rax, 1
	syscall
	ret

read:
	mov rax, 0
	syscall
	ret

fork:
	mov rax, 57
	syscall
	ret

execve: 
	mov rax, 59
	syscall
	ret

asm_waitid:
	mov rax, 247
	//fix register difference as rcx is used by syscall as per x86 intel spec, kernel uses r10
	mov r10, rcx  
	syscall
	ret

_exit:
	mov rax, 60 
	syscall
	ret
