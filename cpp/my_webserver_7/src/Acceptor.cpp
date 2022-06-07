#include "Acceptor.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"

Acceptor::Acceptor(EventLoop* _epl) : epl(_epl), sock(nullptr), accept_ch(nullptr) {
    sock = new Socket();
    InetAddress* addr = new InetAddress("127.0.0.1", 8888);
    sock->bind(addr);
    sock->listen();
    sock->setnonblocking();
    accept_ch = new Channel(epl, sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    accept_ch->setCallback(cb);
    accept_ch->enableReading();
    delete addr;
}

Acceptor::~Acceptor() {
    delete sock;
    delete accept_ch;
}

void Acceptor::acceptConnection() {
    InetAddress* client_addr = new InetAddress();
    Socket* client_sock = new Socket(sock->accept(client_addr));
    printf("new client fd %d, IP: %s, Port: %d\n", client_sock->getFd(), 
    inet_ntoa(client_addr->getSockAddr().sin_addr), ntohs(client_addr->getSockAddr().sin_port));
    client_sock->setnonblocking();
    newConnectionCallback(client_sock);
    delete client_addr;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _cb) {
    newConnectionCallback = _cb;
}