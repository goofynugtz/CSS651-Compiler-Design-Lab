	.file	"program.c"
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
	.cfi_startproc								; It is used at the beginning 
																; of each unction that should 
																; have an entry in .eh_frame.
																; It initializes some internal 
																; data structures and emits 
																; architecture dependent initial 
																; CFI instructions. 
																; Closes the function by 
																; .cfi_endproc.
	endbr64
	pushq	%rbp										; Save address of prev stack frame
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp							; Address of current stack frame
	.cfi_def_cfa_register 6
	subq	$32, %rsp								; Reserve 32 bytes for local variables
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$305419896, -20(%rbp)		; Assigning a = 0x12345678
	leaq	-20(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$120, %al								; Compare if equal to 120 (0x78)
	jne	.L2												; If != then jump to L2 block
	leaq	.LC0(%rip), %rax				; Load string LC0 ("Little Endian")
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L3												; Jump to L3 block
.L2:
	leaq	.LC1(%rip), %rax				; Load string LC1 ("Big Endian")
	movq	%rax, %rdi
	call	puts@PLT								; puts - Library function to print
																; PLT  - Procedure Linkage Table
.L3:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5												; Jump to L5 if above comparision
																; is true
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
