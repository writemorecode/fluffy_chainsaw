.intel_syntax noprefix
.data
        s: .zero 32
.text
.global print

reverse_string_start:
    mov rax, r8
    mov rbx, r8
    add rbx, rcx
    dec rbx
    
    xor rdx, rdx
    mov dl, BYTE PTR [rax]
    cmp dl, 0x2d
    jne reverse_string_loop
    inc rax
    jmp reverse_string_loop

reverse_string_loop:
    cmp rax, rbx
    jg print_end
    mov dl, BYTE PTR [rax]
    mov dh, BYTE PTR [rbx]
    mov BYTE PTR [rax], dh
    mov BYTE PTR [rbx], dl
    inc rax
    dec rbx
    jmp reverse_string_loop

print_end:
        // Add a newline at the end
        mov BYTE PTR [r8 + rcx], 0xa
        inc rcx

        // Call write
        mov rax, 1 
        mov rdi, 1
        lea rsi, [r8]
        mov rdx, rcx
        syscall

        ret

print_loop:
        xor rdx, rdx
        div rbx

        // Convert digit to ASCII char
        add dl, 0x30
        mov BYTE PTR [r8 + rcx], dl
        inc rcx

        cmp rax, 0
        je reverse_string_start

        jmp print_loop

print:
        mov rax, rdi
        mov rbx, 10
        lea r8, [rip + s]
        xor rcx, rcx

        cmp rax, 0
        jge print_loop
        mov BYTE PTR [r8 + rcx], 0x2d
        neg rax
        inc rcx
        jmp print_loop

