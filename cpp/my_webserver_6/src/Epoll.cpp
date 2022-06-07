#include <cstring>
#include <unistd.h>
#include "util.h"
#include "Channel.h"
#include "Epoll.h"

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1) {
    epfd = epoll_create1(0);
    errif(epfd==-1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(events)*MAX_EVENTS);
}

Epoll::~Epoll() {
    if (epfd != -1) {
        close(epfd);
        epfd = - 1;
    }
    delete[] events;
}

void Epoll::updateChannel(Channel* ch) {
    int ch_fd = ch->getFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = ch;
    ev.events = ch->getEvents();
    if (ch->getInEpoll()) {
        errif(epoll_ctl(epfd, EPOLL_CTL_MOD, ch_fd, &ev)==-1, "epoll edit error");
    } else {
        errif(epoll_ctl(epfd, EPOLL_CTL_ADD, ch_fd, &ev)==-1, "epoll add error");
        ch->setInEpoll();
    }
}

std::vector<Channel*> Epoll::poll(int timeout) {
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds==-1, "epoll wait error");
    std::vector<Channel*> activeChannels;
    for (int i=0; i<nfds; ++i) {
        Channel* ch = (Channel*) events[i].data.ptr;
        ch->setRevents(events[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}
