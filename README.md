1. Byron Lopez
2. ID: 028853901

Compile commands: 
1. nano server.c
2. gcc -o echo_server server.c
3. nano client.c
4. gcc -o echo_client client.c
5. nano hello64.s
6. gcc -nostdlib -no-pie -o hello64 hello64.s

Commands ran: 
1. ./echo_server
2. ./echo_client
3. ./hello64

Explanation: 
All the files that we created inside docker has code that perfectly compiles and runs. We were given the skeleton to the code, which helped us build off of the server and implement a safe echo server that listens for any client connections and echoes messages that are sent. The client code is meant to connect to the server, send a line of any user input, and display the servers response. This design is safe because it uses system calls, that avoids random input, and only "echoes" text that is received by user instead of executing unnecessary opeartions. The assembly code uses a call-pop technique, that prints a message without relying on C runtime. 

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
