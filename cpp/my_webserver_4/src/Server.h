#pragma once
#include "EventLoop.h"
#include "Socket.h"

class Server {
    private:
        EventLoop* eventloop;
    public:
        Server(EventLoop*);
        ~Server();

        void handelReadEvent(int);
        void newConnection(Socket *serv_sock);
};