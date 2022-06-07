#pragma once
#include "InetAddress.h"

class Socket{
    private:
        int socket_fd;
    public:
        Socket();
        Socket(int);
        ~Socket();

        void bind(InetAddress*);
        void connect(InetAddress*);
        void listen();
        void setnonBlocking();
        int accept(InetAddress*);
        int getFd() const;
};