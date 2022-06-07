#include "Channel.h"
#include "EventLoop.h"
#include <unistd.h>

Channel::Channel(EventLoop* _eventloop, int _fd) : epl(_eventloop), fd(_fd), events(0), revents(0), in_epoll(false){};

Channel::~Channel() {
    if (fd!=-1) {
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent() {
    epl->addThread(callback);
}

void Channel::enableReading() {
    events |= EPOLLIN | EPOLLET;
    epl->updateChannel(this);
}

int Channel::getFd() const {
    return fd;
}

uint32_t Channel::getEvents() const {
    return events;
}

uint32_t Channel::getRevents() const {
    return revents;
}

bool Channel::getInEpoll() const {
    return in_epoll;
}

void Channel::setInEpoll() {
    in_epoll = true;
}

void Channel::setRevents(uint32_t _rev) {
    revents = _rev;
}

void Channel::setCallback(std::function<void()> _cb) {
    callback = _cb;
}
