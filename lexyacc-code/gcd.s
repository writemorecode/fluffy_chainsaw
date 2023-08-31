.intel_syntax noprefix
.text
.global gcd

gcd:
    mov rax, rdi
    jmp loop

foo:
    sub     rax, rsi
    jmp loop

loop:
    cmp     rax, rsi
    je      gcd_end
    jg      foo 
    sub     rsi, rax
    jmp     loop

gcd_end:
    ret
