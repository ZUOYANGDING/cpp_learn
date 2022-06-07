#include "Connection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include "Util.h"
#include <errno.h>
#include <cstring>
#include <unistd.h>

Connection::Connection(EventLoop* _elp, Socket* _sock) : elp(_elp), sock(_sock), ch(nullptr), in_buffer(new std::string()), read_buffer(nullptr) {
    ch = new Channel(elp, sock->getFd());
    std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
    ch->setCallback(cb);
    ch->enableReading();
    read_buffer = new Buffer();
}

Connection::~Connection() {
    delete ch;
    delete sock;
    delete in_buffer;
    delete read_buffer;
}

void Connection::echo(int _fd) {
    char buf[1024];
    while(true) {
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(_fd, buf, sizeof(buf));
        if (bytes_read>0) {
            read_buffer->append(buf, bytes_read);
        } else if (bytes_read==-1 && errno==EINTR) {
            printf("continue reading....\n");
            continue;
        } else if (bytes_read==-1 && (errno==EAGAIN || errno==EWOULDBLOCK)) {
            printf("finish reading\n");
            printf("message from client fd %d: %s\n", _fd, read_buffer->c_str());
            errif(write(_fd, read_buffer->c_str(), read_buffer->size())==-1, "sock write error");
            read_buffer->clear();
            break;
        } else if (bytes_read == 0) {
            printf("EOF, clietn fd %d disconnected\n", _fd);
            deleteConnectionCallback(sock);
            break;
        }
    }
}

void Connection::setDeleteConnetionCallback(std::function<void(Socket*)> _cb) {
    deleteConnectionCallback = _cb;
}