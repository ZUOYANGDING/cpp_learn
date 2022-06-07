#include <cstring>
#include <unistd.h>
#include <functional>
#include <errno.h>
#include "Server.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"

#define MAX_BUFFER 1024

Server::Server(EventLoop* _eventLoop) : eventloop(_eventLoop){
    Socket *serv_socket = new Socket();
    InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
    serv_socket->bind(serv_addr);
    serv_socket->listen();
    serv_socket->setnonBlocking();

    Channel *serv_channel = new Channel(eventloop, serv_socket->getFd());
    std::function<void()> callback = std::bind(&Server::newConnection, this, serv_socket);
    serv_channel->setCallback(callback);
    serv_channel->enableReading();
}


Server::~Server() {}

void Server::handelReadEvent(int sockfd){
    char buffer[MAX_BUFFER];
    while (true) {
        bzero(&buffer, sizeof(buffer));
        ssize_t bytes_read = read(sockfd, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            printf("message from client fd %d: %s\n", sockfd, buffer);
            write(sockfd, buffer, sizeof(buffer));
        } else if (bytes_read==-1 && errno==EINTR) {
            printf("contine reading...");
            continue;
        } else if (bytes_read==-1 && (errno==EAGAIN || errno==EWOULDBLOCK)) {
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if (bytes_read==0) {
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);
            break;
        }
    }
}

void Server::newConnection(Socket *serv_sock) {
    InetAddress* client_addr = new InetAddress();
    Socket *client_socket = new Socket(serv_sock->accept(client_addr));
    printf("new client fd %d, IP: %s, Port: %d\n", 
                        client_socket->getFd(),
                        inet_ntoa(client_addr->addr.sin_addr),
                        ntohs(client_addr->addr.sin_port));
    client_socket->setnonBlocking();
    Channel* client_channel = new Channel(eventloop, client_socket->getFd());
    std::function<void()> callback = std::bind(&Server::handelReadEvent, this, client_socket->getFd());
    client_channel->setCallback(callback);
    client_channel->enableReading();
}