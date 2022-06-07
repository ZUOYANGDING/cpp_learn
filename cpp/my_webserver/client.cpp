#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "help.h"

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socket_addr;
    bzero(&socket_addr, sizeof(socket_addr));
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket_addr.sin_port = htons(8888);

    // connect to server
    connect(socket_fd, (sockaddr*)&socket_addr, sizeof(socket_addr));

    // write message to server
    while (true) {
        char buf[1024];
        bzero(&buf, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        ssize_t write_bytes = write(socket_fd, buf, sizeof(buf));
        if (write_bytes == -1) {
            printf("socket already disconnected\n");
            break;
        }
        // flush buffer
        bzero(&buf, sizeof(buf));
        // read message from server
        ssize_t read_bytes = read(socket_fd, buf, sizeof(buf));
        if (read_bytes > 0) {
            printf("message from server: %s\n", buf);
        } else if (read_bytes == 0) {
            printf("server socket disconnected\n");
            break;
        } else if (read_bytes == -1) {
            // error
            close(socket_fd);
            errif(true, "socket read error");
        }
    }
    return 0;
}