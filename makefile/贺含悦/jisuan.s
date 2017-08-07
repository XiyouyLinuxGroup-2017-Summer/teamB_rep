	.file	"jisuan.c"
	.section	.rodata
	.align 8
.LC1:
	.string	"\344\273\2161\345\210\26010\347\232\204\347\253\213\346\226\271\344\271\213\345\222\214\344\270\272%d\n"
	.text
	.globl	lifangsum
	.type	lifangsum, @function
lifangsum:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L2
.L3:
	pxor	%xmm0, %xmm0
	cvtsi2sd	-8(%rbp), %xmm0
	movsd	.LC0(%rip), %xmm1
	call	pow@PLT
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sd	-4(%rbp), %xmm0
	addsd	%xmm1, %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L2:
	cmpl	$10, -8(%rbp)
	jle	.L3
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	lifangsum, .-lifangsum
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1074266112
	.ident	"GCC: (Ubuntu 6.3.0-12ubuntu2) 6.3.0 20170406"
	.section	.note.GNU-stack,"",@progbits
