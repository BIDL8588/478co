// server.c -- safe echo server for lab (listen -> accept -> echo)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 31337
#define BACKLOG 4
#define BUF_SIZE 1024

int list_sock(void)
{
    int t_fd;
    struct sockaddr_in addr;
    int top = 1; 

    t_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(t_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    if(setsockopt(t_fd, SOL_SOCKET, SO_REUSEADDR, &top, sizeof(top)) < 0)
    {
        perror("setsockopt");
        close(t_fd); 
        exit(1);
    }

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if(bind(t_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        close(t_fd);
        exit(1);
    }

    if(listen(t_fd, BACKLOG) < 0)
    {
        perror("listen");
        close(t_fd);
        exit(1); 
    }
    printf("Echo server is up and listening on port %d...\n", PORT);
    fflush(stdout);
    return t_fd; 
}

void handle_cli(int conn_fd)
{
    char buf[BUF_SIZE];
    ssize_t n; 
    while((n = recv(conn_fd, buf, sizeof(buf), 0)) > 0)
    {
        send(conn_fd, buf, n, 0);  
    }
    
}

int main(void) {
    int listen_fd = list_sock(); 
    int conn_fd;
    while (1) {
        conn_fd = accept(listen_fd, NULL, NULL);
        if (conn_fd < 0) 
        { 
         perror("accept"); 
         continue; 
        }

        printf("Client connected\n");
        handle_cli(conn_fd);
        close(conn_fd);
        printf("Client disconnected\n");
    }

    close(listen_fd);
    return 0;
}
