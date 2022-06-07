#pragma once
#include <map>

class Acceptor;
class EventLoop;
class Connection;
class Socket;

class Server {
    private:
        EventLoop* elp;
        Acceptor* acpt;
        std::map<int, Connection*> cons;
    public:
        Server(EventLoop*);
        ~Server();
        
        void newConnection(Socket*);
        void deleteConnection(Socket*);
};
