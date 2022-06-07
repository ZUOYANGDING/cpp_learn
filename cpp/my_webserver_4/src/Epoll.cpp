#include <unistd.h>
#include <cstring>
#include "Epoll.h"
#include "util.h"
#include "Channel.h"

#define MAX_EVENTS 1024

Epoll::Epoll() : epfd(-1), events(nullptr) {
    epfd = epoll_create1(0);
    errif(epfd==-1, "epoll create failed");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events)*MAX_EVENTS);
}

Epoll::~Epoll() {
    if (epfd!=-1) {
        close(epfd);
        epfd = -1;
    }
    delete[] events;
}

void Epoll::addFd(int _fd, uint32_t _op) {
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = _fd;
    ev.events = _op;
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, _fd, &ev)==-1, "epoll add error");
}

std::vector<Channel*> Epoll::poll(int timeout) {
    std::vector<Channel*> activeChannel;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds==-1, "epoll wait error");
    for (int i=0; i<nfds; ++i) {
        Channel* ch = (Channel*) events[i].data.ptr;
        ch->setRevents(events[i].events);
        activeChannel.push_back(ch); 
    }
    return activeChannel;
}

void Epoll::updateChannel(Channel* ch) {
    int fd = ch->getFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = ch;
    ev.events = ch->getEvents();
    if (!ch->getInEpoll()) {
        errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev)==-1, "epoll add error");
    } else {
        errif(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev)==-1, "epoll update error");
    }
}
