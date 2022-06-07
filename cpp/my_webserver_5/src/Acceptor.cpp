#include "Socket.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Server.h"

Acceptor::Acceptor(EventLoop* _loop) : eventloop(_loop) {
    socket = new Socket();
    addr = new InetAddress("127.0.0.1", 8888);
    socket->bind(addr);
    socket->listen();
    socket->setnonBlocking();
    acceptChannel = new Channel(eventloop, socket->getFd());
    std::function<void()> callback = std::bind(&Acceptor::acceptConnection, this);
    acceptChannel->setCallback(callback);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor() {
    delete socket;
    delete addr;
    delete acceptChannel;
}

void Acceptor::acceptConnection() {
    newConnectionCallback(socket);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _callback) {
    newConnectionCallback = _callback;
}