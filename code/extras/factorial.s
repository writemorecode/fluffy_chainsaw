.intel_syntax noprefix
.text
.global factorial

factorial:
    // rdi: user input to factorial (n)
    // rax: counter
    mov     rax, 1
    jmp     factorial_loop

factorial_loop:
    // n! = n*(n-1)! , n>=0 , 0! = 1! = 1
    cmp     rdi, 1
    je      factorial_end
    imul    rdi
    dec     rdi
    jmp     factorial_loop

factorial_end:
    ret
