#include "Server.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"
#include "Socket.h"
#include <functional>

Server::Server(EventLoop* _elp) : elp(_elp), acpt(nullptr) {
    acpt = new Acceptor(elp);
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acpt->setNewConnectionCallback(cb);
}

Server::~Server() {
    delete acpt;
}

void Server::newConnection(Socket* sock) {
    Connection* con = new Connection(elp, sock);
    std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    con->setDeleteConnetionCallback(cb);
    cons[sock->getFd()] = con;
}

void Server::deleteConnection(Socket* sock) {
    Connection* con = cons[sock->getFd()];
    cons.erase(sock->getFd());
    delete con;
}