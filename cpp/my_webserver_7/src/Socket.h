#pragma once

class InetAddress;

class Socket{
    private:
        int sock_fd;
    public:
        Socket();
        Socket(int);
        ~Socket();

        void bind(InetAddress*);
        void connect(InetAddress*);
        int accept(InetAddress*);
        void listen();
        void setnonblocking();

        int getFd() const;
};