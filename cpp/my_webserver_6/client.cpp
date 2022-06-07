#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include "src/util.h"
#include "src/Epoll.h"
#include "src/InetAddress.h"
#include "src/Socket.h"
#include "src/Buffer.h"

int main() {
    Socket* client_socket = new Socket();
    InetAddress* client_addr = new InetAddress("127.0.0.1", 8888);
    client_socket->connect(client_addr);

    Buffer* sendBuffer = new Buffer();
    Buffer* readBuffer = new Buffer();

    while (true) {
        sendBuffer->getline();
        ssize_t write_bytes = write(client_socket->getFd(), sendBuffer->c_str(), sendBuffer->size());
        if (write_bytes == -1) {
            printf("socket already disconnected\n");
            break;
        }
        int already_read = 0;
        char buf[1024];
        while (true) {
            bzero(&buf, sizeof(buf));
            ssize_t read_bytes = read(client_socket->getFd(), buf, sizeof(buf));
            if (read_bytes > 0) {
                readBuffer->append(buf, read_bytes);
                already_read += read_bytes;
            } else if (read_bytes == 0) {
                printf("server socket disconnected\n");
                exit(EXIT_SUCCESS);
            } else if (read_bytes == -1) {
                // error
                close(client_socket->getFd());
                errif(true, "socket read error");
                break;
            }
            if (already_read>=sendBuffer->size()) {
                printf("message from server: %s\n", readBuffer->c_str());
                break;
            }
        }
        readBuffer->clear();
        sendBuffer->clear();
    }
    delete readBuffer;
    delete sendBuffer;
    delete client_socket;
    delete client_addr;
    return 0;
}