	.file	"find_max_template.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"The length of the array is %d\n"
	.text
	.globl	Find_Max
	.type	Find_Max, @function

Find_Max:
// prologue - write code for the prologue here
    pushq   %rbp                    # saves base pointer onto stack
    movq    %rsp, %rbp              # set base pointer to the current location on stack
    subq    $20, %rsp               # space for local variables

// Moving local variables to stack
    movl    %edi, -4(%rbp)          # n
    movq    %rsi, -12(%rbp)         # a
    movl    $1, -16(%rbp)           # i
    movl    $0, -20(%rbp)           # max_index

// printf("The length of the array is %d\n", n);
// update this code if necessary to print the length of the array
// this block prints the value of register %edi
// initially the parameter n
	movl	%edi, %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
    jmp     Init_Expr

// reserve space for local variables
/* make a table here the variables from 
 * your c code and the addresses used in assembly 
 * n - address of n  -4(%rbp)
 * a - address of a  -12(%rbp)
 * i - address of i  -16(%bp)
 * max_index - address of offset for a[max_index] -20(%rbp)
*/ 

// this code calls Print_One_Number to 
// print the number found in register %eax - use this code to debug 
// replace $999 with a register or memory address you wish to print
Print_Number:
    movl    (%rax,%rdx,4), %eax
	movl	%eax, %edi
	call	Print_One_Number@PLT
	jmp     Conditional

// write your code to find the index of the maximum value here
Init_Expr:
    movl    -16(%rbp), %edx         # get i
    movl    -4(%rbp), %ebx          # get n
    movl    -20(%rbp), %ecx         # get max_index
    movq    -12(%rbp), %rax         # get base address for array a
    cmpl    $0, %ebx                # compare n:1
    jle     Done

Loop:
    jmp     Print_Number

Conditional:
    movq    -12(%rbp), %rax         # get base address
    movl    -16(%rbp), %edx         # get i
    movl    -20(%rbp), %ecx         # get max_index
    movl    (%rax, %rdx, 4), %edi   # current element
    movl    (%rax, %rcx, 4), %esi   # max element
    cmpl    %edi, %esi              # Compare a[max_index]:a[i]
    jge     End_Conditional         # If >=, exit conditional
    movq    %rdx, -20(%rbp)         # Update max_index
    movl    %edx, %ecx

End_Conditional:
    incl    %edx                    # Increment i
    movl    %edx, -16(%rbp)

Test_Expr:
    cmpl    %ebx, %edx              # Compare i:n
    jl      Loop                    # if <, goto Loop

// prepare the return value
Done:
    movl    -20(%rbp), %eax         # Saves max_index into return register

// the template returns -1, you will need to update this
//	movl	$-1, %eax

// epilogue - complete the epilogue below
    movq    %rbp, %rsp              # Put the stack pointer back where function was called
    popq    %rbp                    # Restore stack frame
	ret

.LFE0:
	.size	Find_Max, .-Find_Max
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
