#pragma once
#include "EventLoop.h"
#include "Socket.h"

class Acceptor;

class Server {
    private:
        EventLoop* eventloop;
        Acceptor* acceptor;
    public:
        Server(EventLoop*);
        ~Server();

        void handelReadEvent(int);
        void newConnection(Socket *serv_sock);
};