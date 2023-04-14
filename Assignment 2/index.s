	.file	"index.c"
	.text
	.section	.rodata
.LC0:
	.string	"Little endian"
.LC1:
	.string	"Big endian"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax

	movl	$1, -20(%rbp)o		// int a = 1; storing value 1 in a

	leaq	-20(%rbp), %rax		// getting address of rbp in  rax , &a

	movq	%rax, -16(%rbp)		// storing the address of a in rbp (stack)

	movq	-16(%rbp), %rax		// moving the value of address of a to rax (temporary register)

	movzbl	(%rax), %eax   	// low 8 bits of rax is copied to eax

	cmpb	$1, %al    		// comparing value eax with 1
	jne	.L2 				// if the above comparison is not true then jump to L2 block
	leaq	.LC0(%rip), %rdi 	// loading string LC0 
	movl	$0, %eax
	call	printf@PLT  		// calling print "little endian"
	jmp	.L3 				// jump to L3 block
.L2:
	leaq	.LC1(%rip), %rdi 	// loading string LC1
	movl	$0, %eax
	call	printf@PLT 		// printing "Big Endian"
.L3: 
	movl	$0, %eax 
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4: