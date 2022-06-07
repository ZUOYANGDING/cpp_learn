#include "Epoll.h"
#include "Channel.h"
#include "ThreadPoll.h"
#include "EventLoop.h"
#include <vector>
#include <iostream>

EventLoop::EventLoop() : ep(nullptr), thread_poll(nullptr), quit(false) {
    ep = new Epoll();
    thread_poll = new ThreadPoll();
}

EventLoop::~EventLoop() {
    delete ep;
    delete thread_poll;
}

void EventLoop::loop() {
    while(!quit) {
        std::vector<Channel*> chs = ep->poll();
        // std::cout<<chs.size()<<std::endl;
        for (auto it=chs.begin(); it!=chs.end(); ++it) {
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel* _ch) {
    ep->updateChannel(_ch);
}

void EventLoop::addThread(std::function<void()> func) {
    thread_poll->add(func);
}