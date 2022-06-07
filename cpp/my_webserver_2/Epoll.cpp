#include <unistd.h>
#include <cstring>
#include "Epoll.h"
#include "help.h"

#define MAX_EVENTS 1024

Epoll::Epoll() : epfd(-1), events(nullptr) {
    epfd = epoll_create1(0);
    errif(epfd==-1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events)*MAX_EVENTS);
}

Epoll::~Epoll() {
    if (epfd != -1) {
        close(epfd);
        epfd = -1;
    }
    delete[] events;
}

void Epoll::addFd(int fd, uint32_t op) {
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = fd;
    ev.events = op;
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev)==-1, "register poll event failed");
}

std::vector<epoll_event> Epoll::poll(int timeout) {
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds==-1, "epoll wait error");
    std::vector<epoll_event> active_events;
    for (int i=0; i<nfds; ++i) {
        active_events.push_back(events[i]);
    }
    return active_events;
}