#include <cstring>
#include "InetAddress.h"

InetAddress::InetAddress() : addr_len(sizeof(sockaddr)) {
    bzero(&sockaddr, sizeof(sockaddr));
}

InetAddress::InetAddress(const char* ip, uint16_t port) : addr_len(sizeof(sockaddr)) {
    bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    sockaddr.sin_port = htons(port);
    addr_len = sizeof(sockaddr);
}

InetAddress::~InetAddress() {
    
}