#include "EventLoop.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Acceptor.h"

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
    delete addr;
}

Acceptor::~Acceptor() {
    delete socket;
    delete acceptChannel;
}

void Acceptor::acceptConnection() {
    InetAddress* client_addr = new InetAddress();
    Socket* client_sock = new Socket(socket->accept(client_addr));
    printf("new client fd %d, IP: %s, port: %d\n", client_sock->getFd(), 
    inet_ntoa(client_addr->getAddr().sin_addr), 
    ntohs(client_addr->getAddr().sin_port));
    client_sock->setnonBlocking();
    newConnctionCallback(client_sock);
    delete client_addr;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _callback) {
    newConnctionCallback = _callback;
}