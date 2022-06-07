#include <cstring>
#include <unistd.h>
#include <errno.h>
#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include "util.h"

#define MAX_BUFFER 1024

Connection::Connection(EventLoop* _loop, Socket* _socket) : eventloop(_loop), socket(_socket), ch(nullptr), 
inBuffer(new std::string), readBuffer(nullptr) {
    ch = new Channel(eventloop, socket->getFd());
    std::function<void()> callback = std::bind(&Connection::echo, this, socket->getFd());
    ch->setCallback(callback);
    ch->enableReading();
    readBuffer = new Buffer();
}

Connection::~Connection() {
    delete ch;
    delete socket;
}

void Connection::echo(int fd) {
    char buff[MAX_BUFFER];
    while(true) {
        bzero(&buff, sizeof(buff));
        ssize_t bytes_read = read(fd, buff, sizeof(buff));
        if (bytes_read > 0) {
            readBuffer->append(buff, bytes_read);
        } else if (bytes_read==-1 && errno==EINTR) {
            printf("continue reading....\n");
            continue;
        } else if (bytes_read==-1 && (errno==EAGAIN || errno==EWOULDBLOCK)) {
            printf("finish reading once, errno: %d\n", errno);
            printf("message from client fd %d: %s\n", fd, readBuffer->c_str());
            errif(write(fd, readBuffer->c_str(), readBuffer->size())==-1, "socket write error");
            readBuffer->clear();
            break;
        } else if (bytes_read == 0) {
            printf("EOF, client fd=%d disconnected\n", fd);
            deleteConnetionCallback(socket);
            break;
        }
    }
}

void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> _callback) {
    deleteConnetionCallback = _callback;
}