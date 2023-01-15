.intel_syntax noprefix
.text
.global lntwo

lntwo_end:
    ret

lntwo_loop:
    cmp rdi, 1
    jle lntwo_end
    sar rdi
    inc rax
    jmp lntwo_loop

lntwo:
    xor rax, rax
    jmp lntwo_loop

