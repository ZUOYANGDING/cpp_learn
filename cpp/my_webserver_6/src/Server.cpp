#include <functional>
#include "EventLoop.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include "Server.h"

Server::Server(EventLoop* _loop) : eventloop(_loop), acceptor(nullptr) {
    acceptor = new Acceptor(eventloop);
    std::function<void(Socket*)> callback = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(callback);
}

Server::~Server() {
    delete acceptor;
}

void Server::newConnection(Socket* socket) {
    Connection* connection = new Connection(eventloop, socket);
    std::function<void(Socket*)> callback = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    connection->setDeleteConnectionCallback(callback);
    connections[socket->getFd()] = connection;
}

void Server::deleteConnection(Socket* socket) {
    Connection* connection = connections[socket->getFd()];
    connections.erase(socket->getFd());
    delete connection;
}