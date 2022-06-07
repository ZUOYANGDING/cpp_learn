#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "InetAddress.h"
#include "util.h"
#include "Socket.h"


Socket::Socket() : socket_fd(-1){
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(socket_fd==-1, "socket create error");
}

Socket::Socket(int _fd) : socket_fd(_fd){
    errif(socket_fd==-1, "socket create error");
}

Socket::~Socket() {
    if (socket_fd != -1) {
        close(socket_fd);
        socket_fd = -1;
    }
}

void Socket::connect(InetAddress* addr) {
    errif(::connect(socket_fd, (sockaddr*)&(addr->addr), addr->addr_len)==-1, 
    "connect error");
}

void Socket::bind(InetAddress* addr) {
    errif(::bind(socket_fd, (sockaddr*)&(addr->addr), addr->addr_len)==-1,
    "bind error");
}

void Socket::listen() {
    errif(::listen(socket_fd, SOMAXCONN)==-1, "listen error");
}

void Socket::setnonBlocking() {
    fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress* addr) {
    int client_fd = ::accept(socket_fd, (sockaddr*)&(addr->addr), &addr->addr_len);
    errif(client_fd==-1, "accept error");
    return client_fd;
}

int Socket::getFd() const {
    return socket_fd;
}