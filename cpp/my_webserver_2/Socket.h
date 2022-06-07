#pragma once

class InetAddress;
class Socket {
    private:
        int sock_fd;
    public:
        Socket();
        Socket(int fd);
        ~Socket();

        void connect(InetAddress*);
        void bind(InetAddress*);
        void listen();
        void setnonBlocking();
        int accept(InetAddress*);
        int getFd();
};