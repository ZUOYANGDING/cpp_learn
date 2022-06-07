#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "help.h"
#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"

int main() {
    Socket *client_socket = new Socket();
    InetAddress *client_addr = new InetAddress("127.0.0.1", 8888);
    client_socket->connect(client_addr);

    // write message to server
    while (true) {
        char buf[1024];
        bzero(&buf, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        ssize_t write_bytes = write(client_socket->getFd(), buf, sizeof(buf));
        if (write_bytes == -1) {
            printf("socket already disconnected\n");
            break;
        }
        // flush buffer
        bzero(&buf, sizeof(buf));
        // read message from server
        ssize_t read_bytes = read(client_socket->getFd(), buf, sizeof(buf));
        if (read_bytes > 0) {
            printf("message from server: %s\n", buf);
        } else if (read_bytes == 0) {
            printf("server socket disconnected\n");
            break;
        } else if (read_bytes == -1) {
            // error
            close(client_socket->getFd());
            errif(true, "socket read error");
        }
    }
    delete client_socket;
    delete client_addr;
    return 0;
}