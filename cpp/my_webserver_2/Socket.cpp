#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "help.h"
#include "InetAddress.h"
#include "Socket.h"

Socket::Socket() : sock_fd(-1) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sock_fd==-1, "socket create failed");
}

Socket::Socket(int fd) :sock_fd(fd) {
    errif(sock_fd==-1, "socket create failed");
}

Socket::~Socket() {
    if (sock_fd!=-1) {
        close(sock_fd);
        sock_fd = -1;
    }
}

void Socket::connect(InetAddress* addr) {
    errif(::connect(sock_fd, (sockaddr*)&(addr->sockaddr), addr->addr_len)==-1,
    "connect error");
}

void Socket::bind(InetAddress* addr) {
    errif(::bind(sock_fd, (sockaddr*)&(addr->sockaddr), addr->addr_len)==-1,
    "socket bind error");
}

void Socket::listen() {
    errif(::listen(sock_fd, SOMAXCONN)==-1, "socket listen error");
}

void Socket::setnonBlocking() {
    fcntl(sock_fd, F_SETFL, fcntl(sock_fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress* addr) {
    int client_fd = 
    ::accept(sock_fd, (sockaddr*)&(addr->sockaddr), &(addr->addr_len));
    errif(client_fd==-1, "socket accept error");
    return client_fd;
}

int Socket::getFd() {
    return sock_fd;
}

