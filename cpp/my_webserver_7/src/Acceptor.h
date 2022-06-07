#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;

class Acceptor {
    private:
        EventLoop* epl;
        Socket* sock;
        Channel* accept_ch;
        std::function<void(Socket*)> newConnectionCallback;
    public:
        Acceptor(EventLoop*);
        ~Acceptor();
        void acceptConnection();
        void setNewConnectionCallback(std::function<void(Socket*)>);
};