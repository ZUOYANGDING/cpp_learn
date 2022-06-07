#pragma once
#include <sys/epoll.h>
#include <functional>

class EventLoop;

class Channel {
    private:
        EventLoop* eventloop;
        int fd;
        uint32_t events;
        uint32_t revents;
        bool inEpoll;
        std::function<void()> callback;
    public:
        Channel(EventLoop*, int);
        ~Channel();
        void handleEvent();
        void enableReading();
        int getFd() const;
        uint32_t getEvents() const;
        uint32_t getRevents() const;
        bool getInEpoll() const;
        void setInEpoll();
        void setRevents(uint32_t);
        void setCallback(std::function<void()>);
};