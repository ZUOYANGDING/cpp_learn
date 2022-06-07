#include "Socket.h"
#include "InetAddress.h"
#include "Util.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/socket.h>

Socket::Socket() : sock_fd(-1){
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sock_fd==-1, "socket create error");
};

Socket::Socket(int _fd) : sock_fd(_fd) {
    errif(sock_fd==-1, "socket create error");
}

Socket::~Socket() {
    if (sock_fd!=-1) {
        close(sock_fd);
        sock_fd = -1;
    }
}

void Socket::bind(InetAddress* addr) {
    struct sockaddr_in _addr = addr->getSockAddr();
    socklen_t _len = addr->getSockLength();
    errif(::bind(sock_fd, (sockaddr*)&_addr, _len)==-1, "bind socket error");
    addr->setInetAddr(_addr, _len);
}

int Socket::accept(InetAddress* addr) {
    struct sockaddr_in _addr;
    socklen_t _len = sizeof(_addr);
    bzero(&_addr, sizeof(_addr));
    int client_fd = ::accept(sock_fd, (sockaddr*)&_addr, &_len);
    errif(client_fd==-1, "accept connection error");
    addr->setInetAddr(_addr, _len);
    return client_fd;
}

void Socket::connect(InetAddress* addr) {
    struct sockaddr_in _addr = addr->getSockAddr();
    socklen_t _len = addr->getSockLength();
    errif(::connect(sock_fd, (sockaddr*)&_addr, _len)==-1, "socket connection error");
    // addr->setInetAddr(_addr, _len);
}

void Socket::listen() {
    errif(::listen(sock_fd, SOMAXCONN)==-1, "socket listen error");
}

void Socket::setnonblocking() {
    fcntl(sock_fd, F_SETFL, fcntl(sock_fd, F_GETFL) | O_NONBLOCK);
}

int Socket::getFd() const {
    return sock_fd;
}
