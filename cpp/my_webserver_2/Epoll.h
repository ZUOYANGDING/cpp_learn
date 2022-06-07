#pragma once
#include <sys/epoll.h>
#include <vector>
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
        std::vector<epoll_event> poll (int timeout=-1);
};