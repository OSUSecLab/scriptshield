.global __vfork
.weak vfork
.type __vfork,@function
.type vfork,@function
__vfork:
vfork:
	jmp enclave_vfork
	pop %rdx
	mov $58,%eax
	syscall
	push %rdx
	mov %rax,%rdi
	jmp __syscall_ret
