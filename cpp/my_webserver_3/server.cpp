#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <errno.h>
#include "help.h"
#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"


#define MAX_EVENTS 1024
#define MAX_BUFFER 1024

void handleReadEvent(int);
void cleanClientInfo(std::vector<InetAddress*>, std::vector<Socket*>);
int main() {
    // init server socket
    Socket *server_socket = new Socket();
    InetAddress *server_addr = new InetAddress("127.0.0.1", 8888);
    server_socket->bind(server_addr);
    server_socket->listen();

    // init Epoll and register server socket event to epoll
    Epoll *ep = new Epoll();
    server_socket->setnonBlocking();
    // hook fd with Epoll by Channel
    Channel *server_channel = new Channel(ep, server_socket->getFd());
    server_channel->enableReading();

    // vector store client info invade mem leak
    std::vector<InetAddress*>  client_addrs;
    std::vector<Socket*> client_sockets;
    // accept client request by epoll
    while(true){
        std::vector<Channel*> events = ep->poll();
        for (int i=0; i<events.size(); ++i) {
            if (events[i]->getFd() == server_socket->getFd()) {
                // new client connection
                InetAddress *client_addr = new InetAddress();
                Socket *client_socket = new Socket(server_socket->accept(client_addr));
                printf("new client fd %d, IP: %s, Port: %d\n", 
                        client_socket->getFd(),
                        inet_ntoa(client_addr->sockaddr.sin_addr),
                        ntohs(client_addr->sockaddr.sin_port));
                // register client connection to epoll
                Channel *client_channel = new Channel(ep, client_socket->getFd());
                client_channel->enableReading();
                client_addrs.push_back(client_addr);
                client_sockets.push_back(client_socket);
            } else if (events[i]->getRevents() & EPOLLIN) {
                // readable event
                handleReadEvent(events[i]->getFd());
            } else {
                printf("other events.....\n");
            }
        }
    }
    // not sure if correct
    cleanClientInfo(client_addrs, client_sockets);
    delete server_socket;
    delete server_addr;
}

void handleReadEvent(int fd) {
    char buf[MAX_BUFFER];
    while (true) {
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(fd, buf, sizeof(buf));
        if (bytes_read > 0) {
            printf("message from client fd %d: %s", fd, buf);
            write(fd, buf, sizeof(buf));
        } else if (bytes_read==-1 && errno==EINTR) {
            printf("coninue reading...");
            continue;
        } else if (bytes_read==-1 && (errno==EAGAIN || errno==EWOULDBLOCK)) {
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if (bytes_read == 0) {
            printf("EOF, client fd %d disconnected\n", fd);
            close(fd);
            break;
        }
    }
}

void cleanClientInfo(std::vector<InetAddress*> addrs, std::vector<Socket*> sockets) {
    std::cout<< "destory client info" <<std::endl;
    std::cout<< addrs.size() <<std::endl;
    std::cout<< sockets.size() <<std::endl;
    for (auto it=addrs.begin(); it!=addrs.end(); ++it) {
        delete *it;
        it = addrs.erase(it);
    }
    std::cout << addrs.size() <<std::endl;
    addrs.clear();
    for (auto it=sockets.begin(); it!=sockets.end(); ++it) {
        delete *it;
        it = sockets.erase(it);
    }
    std::cout<< sockets.size() <<std::endl;
    sockets.clear();
}
