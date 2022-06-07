#pragma once
#include <functional>
#include <string>
class EventLoop;
class Socket;
class Channel;
class Buffer;

class Connection{
    private:
        EventLoop* eventloop;
        Socket* socket;
        Channel* ch;
        std::function<void(Socket*)> deleteConnetionCallback;
        std::string *inBuffer;
        Buffer *readBuffer;
    public:
        Connection(EventLoop*, Socket*);
        ~Connection();
        void echo(int);
        void setDeleteConnectionCallback(std::function<void(Socket*)>);
};