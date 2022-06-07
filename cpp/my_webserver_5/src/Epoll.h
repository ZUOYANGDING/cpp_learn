#pragma once
#include <sys/epoll.h>
#include <vector>

class Channel;
class Epoll{
    private:
        int epfd;
        struct epoll_event *events;
    public:
        Epoll();
        ~Epoll();

        void addFd(int, uint32_t);
        void updateChannel(Channel*);
        std::vector<Channel*> poll(int timeout=-1);
};
