#pragma once
#include <functional>
#include <string>

class EventLoop;
class Socket;
class Channel;
class Buffer;

class Connection {
    private:
        EventLoop* elp;
        Socket* sock;
        Channel* ch;
        std::function<void(Socket*)> deleteConnectionCallback;
        std::string *in_buffer;
        Buffer* read_buffer;
    public:
        Connection(EventLoop*, Socket*);
        ~Connection();

        void echo(int);
        void setDeleteConnetionCallback(std::function<void(Socket*)>);
};