#include "InetAddress.h"
#include <cstring>

InetAddress::InetAddress() : addr_len(sizeof(addr)){
    bzero(&addr, sizeof(addr));
}

InetAddress::InetAddress(const char* ip, uint16_t port) : addr_len(sizeof(addr)) {
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr_len = sizeof(addr);
}

InetAddress::~InetAddress() {}

void InetAddress::setInetAddr(sockaddr_in _addr, socklen_t _len) {
    addr = _addr;
    addr_len = _len;
}

sockaddr_in InetAddress::getAddr() const {
    return addr;
}

socklen_t InetAddress::getAddrLength() const {
    return addr_len;
}

