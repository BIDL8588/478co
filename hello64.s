   .section .text
   .global _start

_start:
    jmp message

code:
    pop    %rsi
    mov    $1, %rax
    mov    $1, %rdi
    mov    $msg_len, %rdx
    syscall

    mov    $60, %rax
    xor    %rdi, %rdi
    syscall

message:
    call code
    .ascii "Hello from CECS478 Lab06 Byron Lopez 028853901\n"
msg_len = . - message - 5
