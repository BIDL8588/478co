server.c (safe echo server)
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

int main(void) {
    int listen_fd = -1, conn_fd = -1;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];
    ssize_t n;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) { perror("socket"); exit(1); }

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(listen_fd, (struct sockaddr*)&addr, sizeof addr) < 0) {
        perror("bind"); close(listen_fd); exit(1);
    }

    if (listen(listen_fd, BACKLOG) < 0) {
        perror("listen"); close(listen_fd); exit(1);
    }

    printf("Echo server listening on port %d
", PORT);

    while (1) {
        conn_fd = accept(listen_fd, NULL, NULL);
        if (conn_fd < 0) { perror("accept"); continue; }

        printf("Client connected
");
        while ((n = recv(conn_fd, buf, sizeof buf, 0)) > 0) {
            send(conn_fd, buf, n, 0);
        }
        close(conn_fd);
        printf("Client disconnected
");
    }

    close(listen_fd);
    return 0;
}
