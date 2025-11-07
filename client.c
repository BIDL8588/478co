client.c (safe client)
// client.c -- connect to localhost:31337, send one line, print reply
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 31337
#define BUF_SIZE 1024

int main(void) {
    int fd;
    struct sockaddr_in srv;
    char buf[BUF_SIZE];

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return 1; }

    memset(&srv, 0, sizeof srv);
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr) <= 0) {
        perror("inet_pton"); close(fd); return 1;
    }

    if (connect(fd, (struct sockaddr*)&srv, sizeof srv) < 0) {
        perror("connect"); close(fd); return 1;
    }

    printf("Connected. Type a line and press Enter:
");
    if (fgets(buf, sizeof buf, stdin) == NULL) { close(fd); return 0; }
    send(fd, buf, strlen(buf), 0);

    ssize_t n = recv(fd, buf, sizeof buf - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("Echo from server: %s", buf);
    }

    close(fd);
    return 0;
}
