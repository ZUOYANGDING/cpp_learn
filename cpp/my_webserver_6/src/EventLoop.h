#pragma once
#include <functional>

class Epoll;
class Channel;
class ThreadPoll;

class EventLoop{
    private:
        Epoll* ep;
        bool quit;
        ThreadPoll* threadpoll;
    public:
        EventLoop();
        ~EventLoop();

        void loop();
        void updateChannel(Channel*);
        void addThread(std::function<void()>);
};