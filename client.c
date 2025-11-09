// client.c -- connect to localhost:31337, send one line, print reply
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 31337
#define BUF_SIZE 1024

int connect_to_server(void) 
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) 
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof srv);
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr) <= 0) 
    {
        perror("inet_pton");
        close(fd);
        exit(1);
    }

    if (connect(fd, (struct sockaddr *)&srv, sizeof srv) < 0) 
    {
        perror("connect");
        close(fd);
        exit(1);
    }

    return fd;
}

void exchange_message(int fd) 
{
    char buf[BUF_SIZE];
    ssize_t n;

    printf("Connected. Type a line and press Enter: ");
    fflush(stdout);

    if (fgets(buf, sizeof buf, stdin) == NULL) {
        if (feof(stdin)) {
            fprintf(stderr, "No input has been received.\n");
        } else {
            perror("fgets");
        }
        return;
    }

    size_t len = strlen(buf);
    if (len == 0) {
        fprintf(stderr, "Empty input.\n");
        return;
    }

    if (send(fd, buf, len, 0) != (ssize_t)len) {
        perror("send");
        return;
    }

    n = recv(fd, buf, sizeof buf - 1, 0);
    if (n < 0) {
        perror("recv");
        return;
    } else if (n == 0) {
        printf("Server closed the connection.\n");
        return;
    }

    buf[n] = '\0';
    printf("Echo from server: %s", buf);
}

int main(void) {
    int fd = connect_to_server();
    exchange_message(fd);
    close(fd);
    return 0;
}
