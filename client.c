// client.c -- connect to localhost:31337, send one line, print reply
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 31337
#define BUF_SIZE 1024
int conn_serv(void)
{
    int c_fd = (AF_INET, SOCK_STREAM, 0); 
    struct sockaddr_in srv;

    if(c_fd < 0)
    {
        perror("socket"); 
        exit(1); 
    }

    memset(&srv, 0, sizeof srv);
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr) <= 0) 
    {
        perror("inet_pton"); 
        close(c_fd); 
        exit (1);
    }

    if (connect(c_fd, (struct sockaddr*)&srv, sizeof srv) < 0) 
    {
        perror("connect"); 
        close(c_fd); 
        return 1;
    }
    return c_fd; 
}

void message_ex(int m_fd)
{
    char buf[BUF_SIZE];
    ssize_t n; 

    printf("Connected. Type a line and press Enter:");
    fflush(stdout);
    if (fgets(buf, sizeof buf, stdin) == NULL) 
    { 
        fprintf(stderr, "No input has been received.\n"); 
        return; 
    }

    send(m_fd, buf, strlen(buf), 0); 
    
    n = recv(m_fd, buf, sizeof buf - 1, 0);
    if(n > 0)
    {
        buf[n] = '\0';
        printf("Echo from server: %s", buf);
    }
    else
    {
        printf("No response or connection closed.\n");
    }
}
int main(void) {
    int fd = conn_serv();
    message_ex(fd);
    close(fd);
    return 0;
}
