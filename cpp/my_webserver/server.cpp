#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <sys/epoll.h>
#include "help.h"


#define MAX_EVENTS 1024
#define MAX_BUFFER 1024

int main() {
    // create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(socket_fd==-1, "socket create error");
    // create struct for ip addr and port
    struct sockaddr_in server_addr;
    // init struct
    bzero(&server_addr, sizeof(server_addr));
    // set addr and port info
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);
    // bind socket to struct
    errif(bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr))==-1, "socket bind failed");
    // listen to socket
    errif(listen(socket_fd, SOMAXCONN)==-1, "socket listen failed");

    // create epoll
    int epfd = epoll_create1(0);
    errif(epfd == -1, "epoll create failed");

    // create epoll event array to store connection event
    struct epoll_event events[MAX_EVENTS];
    // create a epoll event 
    struct epoll_event ev;
    // init event array
    bzero(&events, sizeof(events));
    
    // init ev
    bzero(&ev, sizeof(ev));
    ev.data.fd = socket_fd;
    ev.events = EPOLLIN | EPOLLET;
    // set socket_fd to IO
    setnonBlocking(socket_fd);
    // Register the server socket fd on the epoll instance
    epoll_ctl(epfd, EPOLL_CTL_ADD, socket_fd, &ev);

    // create struct to accept client request (store info of client)
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    bzero(&client_addr, sizeof(client_addr));


    // accept client request by epoll
    while (true) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        // printf("nfds right now: %d\n", nfds);
        errif(nfds==-1, "epoll wait error");
        for (int i=0; i<nfds; ++i) {
            if (events[i].data.fd == socket_fd) {
                // get event from binded socket fd, means new connection coming
                std::cout<< "waiting for connection...." <<std::endl;
                int client_fd = accept(socket_fd, (sockaddr*)&client_addr, &client_addr_len);
                errif(client_fd==-1, "socket accept error");
                printf("new client fd %d, IP: %s, Port:%d\n", client_fd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                
                // register client socket fd on epoll instance
                bzero(&ev, sizeof(ev));
                ev.data.fd = client_fd;
                ev.events = EPOLLIN | EPOLLET;
                setnonBlocking(client_fd);
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
            } else if (events[i].events & EPOLLIN) {
                // readable event
                char buf[MAX_BUFFER];
                while (true) {
                    bzero(&buf, sizeof(buf));
                    ssize_t bytes_read = read(events[i].data.fd, buf, sizeof(buf));
                    if (bytes_read > 0) {
                        printf("message from client fd %d: %s\n", events[i].data.fd, buf);
                        // write message back to client
                        write(events[i].data.fd, buf, sizeof(buf));
                    } else if (bytes_read==-1 && errno==EINTR) {
                        // client disconnect without error
                        printf("client disconnect...");
                        continue;
                    } else if (bytes_read==-1 && (errno==EAGAIN || errno==EWOULDBLOCK)) {
                        // read finish
                        printf("finish reading once, errno: %d\n", errno);
                        break;
                    } else if (bytes_read == 0) {
                        // client disconnect with error
                        printf("EOF, client fd %d disconnected\n", events[i].data.fd);
                        // close fd, and diregister fd from event instance
                        close(events[i].data.fd);
                        // printf("size of events %d\n", nfds);
                        break;
                    }
                }
            } else {
                std::cout<< "other events" <<std::endl;
            }
        }
    }
    close(socket_fd);
    return 0;
}

