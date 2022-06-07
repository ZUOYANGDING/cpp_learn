#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop* _loop, int _fd) : 
eventloop(_loop), fd(_fd), events(0), revents(0), inEpoll(false) {}

Channel::~Channel(){}

void Channel::handleEvent() {
    eventloop->addThread(callback);
}

void Channel::enableReading() {
    events |= EPOLLIN | EPOLLET;
    eventloop->updateChannel(this);
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
    return inEpoll;
}

void Channel::setInEpoll() {
    inEpoll = true;
}

void Channel::setRevents(uint32_t _ev) {
    revents = _ev;
}

void Channel::setCallback(std::function<void()> _callback) {
    callback = _callback;
}

