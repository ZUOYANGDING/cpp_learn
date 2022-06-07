#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "util.h"
#include "InetAddress.h"
#include "Socket.h"

Socket::Socket() : sock_fd(-1) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sock_fd==-1, "socket create error");
}

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
    struct sockaddr_in _addr = addr->getAddr();
    socklen_t _addr_len = addr->getAddrLength();
    errif((::bind(sock_fd, (sockaddr*)&(_addr), _addr_len))==-1, "socket bind error");
    addr->setInetAddr(_addr, _addr_len);
}

void Socket::connect(InetAddress* addr) {
    struct sockaddr_in _addr = addr->getAddr();
    socklen_t _addr_len = addr->getAddrLength();
    errif((::connect(sock_fd, (sockaddr*)&(_addr), _addr_len))==-1, "socket connect error");
}

int Socket::accept(InetAddress* addr) {
    struct sockaddr_in _addr;
    socklen_t _addr_len = sizeof(addr);
    bzero(&_addr, sizeof(_addr));
    int client_id = ::accept(sock_fd, (sockaddr*)&(_addr), &_addr_len);
    errif(client_id==-1, "socket accept error");
    addr->setInetAddr(_addr, _addr_len);
    return client_id;
}

void Socket::listen() {
    errif((::listen(sock_fd, SOMAXCONN))==-1, "socket listen error");
}

void Socket::setnonBlocking() {
    fcntl(sock_fd, F_SETFL, fcntl(sock_fd, F_GETFD) |  O_NONBLOCK);
}

int Socket::getFd() const {
    return sock_fd;
}