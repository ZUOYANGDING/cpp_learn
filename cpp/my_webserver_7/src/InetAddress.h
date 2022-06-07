#pragma once
#include <arpa/inet.h>

class InetAddress{
    private:
        struct sockaddr_in addr;
        socklen_t addr_len;
    public:
        InetAddress();
        InetAddress(const char*, uint16_t);
        ~InetAddress();
        void setInetAddr(sockaddr_in, socklen_t);
        sockaddr_in getSockAddr() const;
        socklen_t getSockLength() const;
};
