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

std::vector<Channel*> Epoll::poll(int timeout) {
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds==-1, "epoll wait error");
    std::vector<Channel*> active_events;
    for (int i=0; i<nfds; ++i) {
        Channel* channel = (Channel*) events[i].data.ptr;
        channel->setRevents(events[i].events);
        active_events.push_back(channel);
    }
    return active_events;
}

void Epoll::updateChannel(Channel* channel) {
    int fd = channel->getFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    // let ptr point to channel
    ev.data.ptr = channel;
    // set events to channel event
    ev.events = channel->getEvents();
    if (channel->getInEpoll()) {
        errif(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev)==-1, "epoll modify error");
    } else {
        errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev)==-1, "epoll add error");
        channel->setInEpoll();
    }
 }