.intel_syntax noprefix
.text
.global gcd

gcd:
    mov rax, rdi
    jmp loop

g:
    sub     rax, rsi
    jmp loop

loop:
    cmp     rax, rsi
    je      gcd_end
    jg      g 
    sub     rsi, rax
    jmp     loop

gcd_end:
    ret
