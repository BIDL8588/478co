1. Byron Lopez
2. ID: 028853901

Compile commands: 
1. nano server.c
2. gcc echo_server -o server.c
3. nano client.c
4. gcc echo_client -o client.c
5. nano hello64.s
6. gcc -nostdlib -no-pie -o hello64 hello64.s

Commands ran: 
./echo_server
./echo_client
./hello64


Assembly demo: 
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
    .ascii "Hello from CECS478 Lab06  ^`^t Byron Lopez 028853901\n"
msg_len = . - message - 5
