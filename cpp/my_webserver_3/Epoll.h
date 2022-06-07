#pragma once
#include <sys/epoll.h>
#include <vector>
#include "Channel.h"

class Epoll {
    private:
        // epoll fd
        int epfd;
        // epoll event struct in kernel
        struct epoll_event *events;
    public:
        Epoll();
        ~Epoll();
        
        void addFd(int fd, uint32_t op);
        void updateChannel(Channel*);
        std::vector<Channel*> poll (int timeout=-1);
};