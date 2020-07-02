	.file	"asm++i.cpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp ; 栈底指针rbp入栈
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp ; 将栈顶rsp中的数值放入rbp中
	.cfi_def_cfa_register 6
	movl	$10, -4(%rbp) ; 将数值10放入 相对rbp指定内存位置 向下偏移4个字节位置
	addl	$1, -4(%rbp) ; 将 rbp指定位置向下偏移4个字节的位置加1
	movl	$0, %eax ; 将eax中的内容清除
	popq	%rbp ; 将rsp指定内存位置中的4/8个字节的内容放入rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
