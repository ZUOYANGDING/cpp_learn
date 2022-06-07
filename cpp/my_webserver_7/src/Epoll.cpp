#include "Epoll.h"
#include "Channel.h"
#include "Util.h"
#include <cstring>
#include <unistd.h>
#include <iostream>

#define MAX_EVENTS 1000

Epoll::Epoll() : fd(-1), events(nullptr) {
    fd = epoll_create1(0);
    errif(fd==-1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events)*MAX_EVENTS);
}

Epoll::~Epoll() {
    if (fd!=-1) {
        close(fd);
        fd = -1;
    }
    delete[] events;
}

std::vector<Channel*> Epoll::poll(int timeout) {
    std::vector<Channel*> active_channels;
    // std::cout<<"wait...."<<std::endl;
    int fds = epoll_wait(fd, events, MAX_EVENTS, timeout);
    errif(fds==-1, "epoll wait error");
    for (int i=0; i<fds; ++i) {
        Channel* ch = (Channel*) events[i].data.ptr;
        ch->setRevents(events[i].events);
        active_channels.push_back(ch);
    }
    return active_channels;
}

void Epoll::updateChannel(Channel* _ch) {
    int _fd = _ch->getFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = _ch;
    ev.events = _ch->getEvents();
    if (!_ch->getInEpoll()) {
        // std::cout<<"add"<<std::endl;
        errif(epoll_ctl(fd, EPOLL_CTL_ADD, _fd, &ev)==-1, "epoll add error");
        _ch->setInEpoll();
    } else {
        // std::cout<<"update"<<std::endl;
        errif(epoll_ctl(fd, EPOLL_CTL_MOD, _fd, &ev)==-1, "epoll modify error");
    }
}