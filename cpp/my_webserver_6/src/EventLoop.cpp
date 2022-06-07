#include <vector>
#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include "ThreadPoll.h"

EventLoop::EventLoop() : ep(nullptr), quit(false) {
    ep = new Epoll();
    threadpoll = new ThreadPoll();
}

EventLoop::~EventLoop() {
    delete ep;
}

void EventLoop::loop() {
    while(!quit) {
        std::vector<Channel*> chs;
        chs = ep->poll();
        for (auto it=chs.begin(); it!=chs.end(); ++it) {
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel* ch) {
    ep->updateChannel(ch);
}

void EventLoop::addThread(std::function<void()> func) {
    threadpoll->add(func);
}